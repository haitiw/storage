#include "data_global.h"
void *pthread_client_request(void *arg) {
  printf("client_request\n");
  return arg;
}