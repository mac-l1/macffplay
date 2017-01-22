#ifndef __LOG_H
#define __LOG_H

#include <stdio.h>
#include <pthread.h>

#define DBG(fmt, ...) do { printf("D(%p): %s:%d " fmt "\n", pthread_self(),  __func__, __LINE__, ##__VA_ARGS__); fflush(stdout); } while (0)
#define ERROR(fmt, ...) do { printf("E(%p): %s:%d " fmt "\n", pthread_self(),  __func__, __LINE__, ##__VA_ARGS__); fflush(stdout); } while (0)
#define INFO(fmt, ...) do { printf("I(%p): %s:%d " fmt "\n", pthread_self(), __func__, __LINE__, ##__VA_ARGS__); fflush(stdout); } while (0)

#define FIN() do { printf("->F(%p): %s#%d \n", pthread_self(), __PRETTY_FUNCTION__,__LINE__); fflush(stdout); } while(0)
#define FOUT() do { printf("<-F(%p): %s#%d \n", pthread_self(), __PRETTY_FUNCTION__,__LINE__); fflush(stdout); } while(0)
#define FUN() do { printf("==F(%p): %s#%d \n", pthread_self(), __PRETTY_FUNCTION__,__LINE__); fflush(stdout); } while(0)

#endif

