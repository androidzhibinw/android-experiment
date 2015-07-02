#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage setschedular pid\n");
        return -1;
    }
    int pid =atoi(argv[1]);
    printf("pid is %d",pid);
    struct sched_param sp = { .sched_priority = 99 };
    int ret;

    ret = sched_setscheduler(pid, SCHED_RR, &sp);
    if (ret != 0) {
        printf("sched_setscheduler fail\n");
        printf("errno is %d",errno);
        return 1;
    } else {
        printf("sched_setscheduler success for %d",pid);
    }
    return 0;
}
