#include "data_global.h"
void *pthread_sqlite(void *arg) {
    printf("sqlite\n");
    return arg;
}