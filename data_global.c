#include "data_global.h"


pthread_mutex_t mutex_client_request,
        		mutex_refresh,
        		mutex_sqlite,
	        	mutex_transfer,
	        	mutex_sms,
	        	mutex_buzzer,
	         	mutex_led;

pthread_cond_t  cond_client_request,
        		cond_refresh,
        		cond_sqlite,
	        	cond_transfer,
	        	cond_sms,
	        	cond_buzzer,
	         	cond_led;

pthread_t tid_client_request, 
          tid_sqlite, 
          tid_refresh, 
          tid_sms,                                                 
          tid_buzzer, 
          tid_transfer, 
          tid_led;

int msgid;
int shmid;
int semid;

key_t sem_key;
key_t shm_key;
key_t key;


