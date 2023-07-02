#include "data_global.h"
void *pthread_refresh(void *arg) { 
    printf("refresh\n");
    return arg;
}