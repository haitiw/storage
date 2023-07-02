#ifndef __DATA__GLOBAL__H__
#define __DATA__GLOBAL__H__

#include <pthread.h>
#include <signal.h>
#include <stdio.h>

/*********************************************************
  全局的结构体声明
 *********************************************************/

typedef  unsigned char uint8_t;
typedef  unsigned short uint16_t;
typedef  unsigned int uint32_t;

//考虑到内存对齐的问题
struct makeru_zigbee_info{
	uint8_t head[3]; //标识位: 'm' 's' 'm'  makeru-security-monitor  
	uint8_t type;	 //数据类型  'z'---zigbee  'a'---a9
	float temperature; //温度
	float humidity;  //湿度
	float tempMIN;//温度下限
	float tempMAX;//温度上限 
	float humidityMIN;   //湿度下限
	float humidityMAX;   //湿度上限
	uint32_t reserved[2]; //保留扩展位，默认填充0
};

struct makeru_a9_info{
	uint8_t head[3]; //标识位: 'm' 's' 'm'  makeru-security-monitor  
	uint8_t type;	 //数据类型  'z'---zigbee  'a'---a9
	float adc;
	short gyrox;   //陀螺仪数据
	short gyroy;
	short gyroz;
	short  aacx;  //加速计数据
	short  aacy;
	short aacz;
	uint32_t reserved[2]; //保留扩展位，默认填充0
};


pthread_mutex_t mutex_client_request, 
                mutex_sqlite,
                mutex_refresh,
                mutex_sms,
                mutex_buzzer,
                mutex_transfer,
                mutex_led;

pthread_cond_t cond_client_request, 
               cond_sqlite,
               cond_refresh,
               cond_sms,
               cond_buzzer,
               cond_transfer,
               cond_led;
               
pthread_t tid_client_request, 
          tid_sqlite,
          tid_refresh,
          tid_sms,
          tid_buzzer,
          tid_transfer,
          tid_led;

void *pthread_client_request(void *arg);
void *pthread_sqlite(void *arg);
void *pthread_refresh(void *arg);
void *pthread_sms(void *arg);
void *pthread_buzzer(void *arg);
void *pthread_transfer(void *arg);
void *pthread_led(void *arg);

#endif