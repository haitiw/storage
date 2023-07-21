/*************************************************************************
*File Name: leddev.c
*Author: haitiw
*mail: haitiwplus@gmail.com
*Created Time: Wed 12 Jul 2023 06:21:23 AM UTC
 ************************************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "chardev.h"

const char *name = "buzzer";
unsigned int  major ;
struct class *cls;
struct device *dev;
#define GPD0CON 0x114000A0    
#define PWM 0x139D0000


void __iomem * gpd0con_vir;
void __iomem * pwmtcfg0_vir;
void __iomem * pwmtcfg1_vir;
void __iomem * pwmtcon_vir;
void __iomem * pwmtcntb0_vir;
void __iomem * pwmtcmpb0_vir;


char kbuf[] = {'1','2','3','4'};

loff_t buzzer_llseek(struct file *filp, loff_t offset, int cnt)
{

	printk("---->%s--->%d\n",__func__,__LINE__);
	return 0;
}

ssize_t buzzer_read(struct file *filp, char __user *usrbuf, size_t count, loff_t *offset)
{
	int bytes = 0;
	printk("---->%s--->%d\n",__func__,__LINE__);

	bytes =	copy_to_user(usrbuf,kbuf,4);
	if(bytes > 0){
		printk("copy_to_user failed!\n");
	}

	return 0;
}

ssize_t buzzer_write(struct file *filp, const char __user *usrbuf, size_t size, loff_t *offset)
{
	int bytes = 0;
	printk("---->%s--->%d\n",__func__,__LINE__);

	bytes = copy_from_user(kbuf,usrbuf,4);
	if(bytes > 0){
		printk("copy_from_user failed\n");
		return -1;
	}
	printk("copy_from_user usrbuf:%c\n",kbuf[0]);
	return 0;
}


long buzzer_ioctl(struct file *filp, unsigned int cmd, unsigned long args)
{
	led_desc_t *led = (led_desc_t *)args;
	printk("---->%s--->%d\n",__func__,__LINE__);

	switch(cmd){
		case FS_BUZZER_ON:
			printk("FS_BUZZER_ON. \n");
            writel(readl(pwmtcon_vir) | 1, pwmtcon_vir);

			break;
		case FS_BUZZER_OFF:
			printk("FS_BUZZER_OFF. \n");
            writel(readl(pwmtcon_vir) & 0, pwmtcon_vir);
			break;
		default:
			printk("default :....\n");
			break;
	}
	return 0;
}


int buzzer_open(struct inode *inode, struct file *filp)
{
	//硬件的初始化工作--收发数据的初始化
	printk("---->%s--->%d\n",__func__,__LINE__);
	return 0;
}

int buzzer_close(struct inode *inode, struct file *filp)
{
	printk("---->%s--->%d\n",__func__,__LINE__);
	return 0;
}

const struct file_operations fops = {
	.open=buzzer_open,
	.llseek=buzzer_llseek,
	.read=buzzer_read,
	.write=buzzer_write,
	.unlocked_ioctl=buzzer_ioctl,
	.release=buzzer_close,
};


void gpio_ioremap(void)
{
	gpd0con_vir = ioremap(GPD0CON,4);//gpx2con 4字节
		
	pwmtcfg0_vir = ioremap(PWM,20);
	pwmtcfg1_vir = pwmtcfg0_vir + 4;
	pwmtcon_vir = pwmtcfg0_vir + 8;
    pwmtcntb0_vir = pwmtcfg0_vir + 0x0c;
    pwmtcmpb0_vir = pwmtcfg0_vir + 0x10;

	/*1.将GPD0_0引脚设置成PWM0的输出引脚*/	
	writel(readl(gpd0con_vir) & (~(0XF))| 0x2,gpd0con_vir);

	/*2.设置PWM0的一级分频	一级分频倍数设置为100倍*/
	writel((readl(pwmtcfg0_vir) & (~(0XFF))| 99),pwmtcfg0_vir);
	/*3.设置PWM0的二级分频	二级分频倍数设置为1倍  递减计数器递减频率 = PLCK / (99 + 1) / 1 = 1M*/ 
	writel((readl(pwmtcfg1_vir) & (~(0XF))), pwmtcfg1_vir);
    /*4.设置PWM0为自动重装载，使其能够产生连续的脉冲信号*/
    writel(readl(pwmtcon_vir) | (1 << 3), pwmtcon_vir);
    /*5.设置PWM0的频率为1000HZ*/
    writel(10000, pwmtcntb0_vir);
	/*6.设置PWM0的占空比为60%*/
    writel(6000, pwmtcmpb0_vir);
    /*7.将TCNTB0中的值手动装载到递减计数器*/
    writel(readl(pwmtcon_vir) | (1 << 1), pwmtcon_vir);
	/*8.关闭手动更新*/
    writel(readl(pwmtcon_vir) & (~(1 << 1)), pwmtcon_vir);
	/*9.使能PWM0，递减计数器开始递减*/
    writel(readl(pwmtcon_vir) | 1, pwmtcon_vir);
}


static int __init buzzer_init(void)
{
	printk("---->%s--->%d\n",__func__,__LINE__);
	
	major = register_chrdev(0,name,&fops); 
	if(major <= 0){
		printk("register_chrdev failed!\n");
	}
	printk("register_chrdev success .major: %d\n",major);
	

	cls = class_create(THIS_MODULE,name);
	if(cls == NULL){
		printk("class_create failed!\n");
	}
	dev = device_create(cls, NULL,MKDEV(major,0),NULL,"buzzer1");
	if(dev == NULL){	
		printk("device_create failed!\n");
	}

	gpio_ioremap();
	return 0;
}

void viraddr_iounmap(void)
{
	iounmap(PWM);
}

static void __exit buzzer_exit(void)
{
	printk("---->%s--->%d\n",__func__,__LINE__);
	viraddr_iounmap();
	device_destroy(cls,MKDEV(major,0));
	class_destroy(cls);
	unregister_chrdev(major,name);
}


module_init(buzzer_init);
module_exit(buzzer_exit);
MODULE_LICENSE("GPL");

