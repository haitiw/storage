/*************************************************************************
*File Name: main.c
*Author: TianFan
*mail: whywhy303918@Gmail.com
*Created Time: 2023年06月30日 星期五 10时28分05秒
 ************************************************************************/
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
void ReleaseSignalResource();

void *pthread_client_request(void *arg);
void *pthread_sqlite(void *arg);
void *pthread_refresh(void *arg);
void *pthread_sms(void *arg);
void *pthread_buzzer(void *arg);
void *pthread_transfer(void *arg);
void *pthread_led(void *arg);

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

int main(int argc, const char *argv[]){
    struct sigaction act; // 定义一个struct sigaction类型的变量act，用于设置信号处理函数
    act.sa_handler = ReleaseSignalResource; // 设置act的信号处理函数为ReleaseSignalResource
    act.sa_flags = 0; // 设置act的标志位为0
    sigemptyset(&act.sa_mask); // 将act的信号掩码sa_mask清空

    //初始化互斥锁
    pthread_mutex_init(&mutex_client_request, NULL);
    pthread_mutex_init(&mutex_sqlite, NULL);
    pthread_mutex_init(&mutex_refresh, NULL);
    pthread_mutex_init(&mutex_sms, NULL);
    pthread_mutex_init(&mutex_buzzer, NULL);
    pthread_mutex_init(&mutex_transfer, NULL);
    pthread_mutex_init(&mutex_led, NULL);
    
    pthread_cond_init(&cond_client_request, NULL);
    pthread_cond_init(&cond_sqlite, NULL);
    pthread_cond_init(&cond_refresh, NULL);
    pthread_cond_init(&cond_sms, NULL);
    pthread_cond_init(&cond_buzzer, NULL);
    pthread_cond_init(&cond_transfer, NULL);
    pthread_cond_init(&cond_led, NULL);
    
    pthread_create(&tid_client_request, NULL, pthread_client_request, NULL);
    pthread_create(&tid_sqlite, NULL, pthread_sqlite, NULL);
    pthread_create(&tid_refresh, NULL ,pthread_refresh, NULL);
    pthread_create(&tid_sms, NULL, pthread_sms, NULL);
    pthread_create(&tid_buzzer, NULL, pthread_buzzer, NULL);
    pthread_create(&tid_led, NULL, pthread_led, NULL);

    sigaction(SIGINT,&act,NULL); // 设置SIGINT信号的处理函数为handle
}

void ReleaseSignalResource(int arg) {
  pthread_mutex_destroy(&mutex_client_request);
  pthread_mutex_destroy(&mutex_refresh);
  pthread_mutex_destroy(&mutex_sqlite);
  pthread_mutex_destroy(&mutex_transfer);
  pthread_mutex_destroy(&mutex_sms);
  pthread_mutex_destroy(&mutex_buzzer);
  pthread_mutex_destroy(&mutex_led);

  pthread_cond_destroy(&cond_client_request);
  pthread_cond_destroy(&cond_refresh);
  pthread_cond_destroy(&cond_sqlite);
  pthread_cond_destroy(&cond_transfer);
  pthread_cond_destroy(&cond_sms);
  pthread_cond_destroy(&cond_buzzer);
  pthread_cond_destroy(&cond_led);

  pthread_detach(tid_client_request);
  pthread_detach(tid_refresh);
  pthread_detach(tid_sqlite);
  pthread_detach(tid_transfer);
  pthread_detach(tid_sms);
  pthread_detach(tid_buzzer);
  pthread_detach(tid_led);
}
void *pthread_client_request(void *arg) { printf("client_request\n"); }
void *pthread_sqlite(void *arg) { printf("sqlite\n"); }
void *pthread_refresh(void *arg) { printf("refresh\n"); }
void *pthread_sms(void *arg) { printf("sms\n"); }
void *pthread_buzzer(void *arg) { printf("buzzer\n"); }
void *pthread_led(void *arg) { printf("led\n"); }