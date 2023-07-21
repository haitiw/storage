/*************************************************************************
	#	 FileName	: test.c
	#	 Author		: fengjunhui 
	#	 Email		: 18883765905@163.com 
	#	 Created	: 2017年07月03日 星期一 15时48分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/limits.h>
#include <errno.h>
#include "../dev/chardev.h"

#define BUZZER_DEVICE "/dev/buzzer1"
#define MAX_BUFFER_SIZE PIPE_BUF

int main(int argc, const char *argv[])
{
	int i = 0,j = 3;
	int nread;
	int buzzer_control;
	int buzzer_fd,fifo_fd;
	led_desc_t led;
	char *data;

	buzzer_fd = open(BUZZER_DEVICE,O_RDWR);
	if(buzzer_fd < 0){
		printf("open failed !\n");
	}
	printf("open device success! led_fd: %d\n",buzzer_fd);


    printf("Content-type: text/html;charset=utf-8\n\n");
    printf("<html>\n");
    printf("<head><title>cgi control buzzer web</title></head>\n");
    printf("<body>\n");
    printf("<p>led is setted successful! you can watch the buzzer change</p>\n");
    //printf("<p><a herf=http://192.168.1.50/led.html>go back</a></p>\n");
	printf("<a href=\"/buzzer.html\">go back buzzer control page </a>");
	printf("</body>\n");

    data = getenv("QUERY_STRING");   //getenv()读取环境变量的当前值的函数 

    if(sscanf(data,"buzzer_control=%d",&buzzer_control)!=1)
    {   //利用sscnaf（）函数的特点将环境变量分别提取出led_control和led_state这两个值
        printf("<p>please input right"); 
        printf("</p>");
    } 
    printf("<p>buzzer_control = %d</p>", buzzer_control);
    if(buzzer_control < 0 || buzzer_control > 1) { 
        printf("<p>Please input buzzer_control = 0 or 1!"); 
        printf("</p>");
    } 

	led.led_num   = buzzer_control;
	
	if(buzzer_control == 0){
		ioctl(buzzer_fd,FS_BUZZER_OFF,&led);
    } else if (buzzer_control == 1) {
        ioctl(buzzer_fd, FS_BUZZER_ON, &led);
    }

        close(buzzer_fd);
    printf("</html>\n");

	return 0;
}
