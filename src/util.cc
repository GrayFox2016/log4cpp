#include "util.h"

pid_t GetThreadId() {
    return syscall(SYS_gettid);
}

uint32_t GetCoroutineId() {
    // haven't been implemented
    return 0;
}
