#include "data_global.h"
void *pthread_led(void *arg) { 
    printf("led\n");
    return arg; 
}