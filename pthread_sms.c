#include "data_global.h"
void *pthread_sms(void *arg) { 
    printf("sms\n"); 
    return arg;    
}