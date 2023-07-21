#ifndef __DATA__GLOBAL__H__
#define __DATA__GLOBAL__H__
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define MONITOR_NUM  2  //仓库房间
#define QUEUE_MSG_LEN  1024  //消息队列 

/*********************************************************
  全局的结构体声明
 *********************************************************/

typedef  unsigned char uint8_t;
typedef  unsigned short uint16_t;
typedef  unsigned int uint32_t;

//考虑到内存对齐的问题
struct zigbeeInfo{
	uint8_t head[3]; //标识位: 'm' 's' 'm'  makeru-security-monitor  
	uint8_t type;	 //数据类型  'z'---zigbee  'a'---a9
	float temperature; //温度
	float temperatureMIN;//温度下限
	float temperatureMAX;//温度上限 
	float humidity;  //湿度
	float humidityMIN;   //湿度下限
	float humidityMAX;   //湿度上限
	uint32_t reserved[2]; //保留扩展位，默认填充0
};

struct a9Info{
	uint8_t head[3]; //标识位: 'm' 's' 'm'  makeru-security-monitor  
	uint8_t type;	 //数据类型  'z'---zigbee  'a'---a9
	float adc;
	short gyrox;   //陀螺仪数据
	short gyroy;
	short gyroz;
	short  accelerationx;  //加速计数据
	short  accelerationy;
	short accelerationz;
	uint32_t reserved[2]; //保留扩展位，默认填充0
};

struct environmentalData{
    struct zigbeeInfo zigbeeInfo;
    struct a9Info A9Info;
    uint32_t reserve[2];  //拓展接口，默认填充0
};

struct warehouseData{

    struct environmentalData warehouseNumber[MONITOR_NUM];
};

void *pthread_client_request(void *arg); //接收CGI 等的请求  
void *pthread_sqlite(void *arg);         //刷新共享内存数据线程
void *pthread_refresh(void *arg);        //数据库线程，保存数据库的数据
void *pthread_buzzer(void *arg);
void *pthread_transfer(void *arg);       //接收ZigBee的数据并解析  
void *pthread_led(void *arg);
void *pthread_sms(void *arg);

/*********************************************************
  全局的消息队列传递的结构体声明
 *********************************************************/
//消息队列结构体

struct msg
{
	long type;//从消息队列接收消息时用于判断的消息类型
	long msgtype;//具体的消息类型
	unsigned char text[QUEUE_MSG_LEN];//消息正文
};

#endif
