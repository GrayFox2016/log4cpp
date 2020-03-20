#ifndef __UTIL_H__
#define __UTIL_H__

#include <pthread.h>
#include <unistd.h>
// #include <sys/types.h>
#include <sys/syscall.h>
// #include <stdio.h>
#include <stdint.h>

pid_t GetThreadId();
uint32_t GetCoroutineId();

#endif // __UTIL_H__
