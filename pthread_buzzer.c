#include "data_global.h"
void *pthread_buzzer(void *arg) { 
    printf("buzzer\n");
    return arg;
}