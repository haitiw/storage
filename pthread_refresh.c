#include "data_global.h"

#include "sem.h"

#define N 1024   //获取1024个字节
extern int shmid;
extern int msgid;
extern int semid;

extern key_t sem_key;
extern key_t shm_key;
extern key_t key;

extern struct warehouseData wareData;

struct sharedMemoryAddress{
    char sharedMemoryStatus;
    struct warehouseData wareData;
};

struct sharedMemoryAddress *shm_buf;
void file_env_info_struct(struct warehouseData *addr,char warehouseId);

void *pthread_refresh(void *arg) { 
    printf("refresh\n");
    //初始化信号量
    if((sem_key = ftok("/tmp",101)) < 0){
        perror("ftok failed .\n");
        exit(-1);
    }

    semid = semget(sem_key,1,IPC_CREAT|IPC_EXCL|0666);
	if(semid == -1)	{
		if(errno == EEXIST){
			semid = semget(sem_key,1,0777);
		}else{
			perror("fail to semget");
			exit(1);
		}
	}else{
		init_sem(semid, 0, 1);
	}
	//开辟一块共享内存
    if((shm_key = ftok("/tmp",'i')) < 0){
        perror("ftok failed .\n");
        exit(-1);
    }

	shmid = shmget(shm_key,N,IPC_CREAT|IPC_EXCL|0666);
	if(shmid == -1)	{
		if(errno == EEXIST){
			shmid = shmget(key,N,0777);
		}else{
			perror("fail to shmget");
			exit(1);
		}
	}
    //将共享内存和与信号量挂在一起
	if((shm_buf = (struct sharedMemoryAddress *)shmat(shmid,NULL,0)) == (void *)-1)
	{
		perror("fail to shmat");
		exit(1);
	}
    memset(shm_buf,0,sizeof(struct sharedMemoryAddress));

    printf("pthread_refresh ......>>>>>>>\n");
    while(1){
        sem_p(semid,0);
		shm_buf->sharedMemoryStatus = 1;
		file_env_info_struct(&shm_buf->wareData,shm_buf->sharedMemoryStatus);
		sleep(1);
		sem_v(semid,0);
    }
    return arg;
}

void file_env_info_struct(struct warehouseData *addr,char warehouseId){
    int environmentalDataSlaveAddress = sizeof(struct warehouseData);


	printf("environmentalDataSlaveAddress = %d.\n",environmentalDataSlaveAddress);  

    addr->warehouseNumber[warehouseId].zigbeeInfo.temperature = 24.6;
    addr->warehouseNumber[warehouseId].zigbeeInfo.temperatureMAX = 30.0;
    addr->warehouseNumber[warehouseId].zigbeeInfo.temperatureMIN = 10.0;
    addr->warehouseNumber[warehouseId].zigbeeInfo.humidity = 58;
    addr->warehouseNumber[warehouseId].zigbeeInfo.humidityMAX = 30;
    addr->warehouseNumber[warehouseId].zigbeeInfo.humidityMIN = 80;

    addr->warehouseNumber[warehouseId].A9Info.adc = 89;
    addr->warehouseNumber[warehouseId].A9Info.gyrox = 89;
    addr->warehouseNumber[warehouseId].A9Info.gyroy = 89;
    addr->warehouseNumber[warehouseId].A9Info.gyroz = 89;
    addr->warehouseNumber[warehouseId].A9Info.accelerationx = 89;
    addr->warehouseNumber[warehouseId].A9Info.accelerationy = 89;
    addr->warehouseNumber[warehouseId].A9Info.accelerationz = 89;
    

}
