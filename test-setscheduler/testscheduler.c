#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
int do_huge_work();
int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage testschedular 0/1/2\n");
        printf(" testschedular 0 do nothing\n");
        printf(" testschedular 1 change priority\n");
        printf(" testschedular 2 change priorityand policy\n");
        return -1;
    }
    int option =atoi(argv[1]);
    if(option >= 1) {
        int ret = setpriority(PRIO_PROCESS,getpid(),-20);
        if (ret !=0) {
            printf("setpriority fail\n");
            printf("errno is %d",errno);
            return 1;
        } else {
            printf("setpriority success\n");
        }
    } 
    if (option > 1) {
        struct sched_param sp = { .sched_priority = 99 };
        int ret;

        ret = sched_setscheduler(0, SCHED_RR, &sp);
        if (ret != 0) {
            printf("sched_setscheduler fail\n");
            printf("errno is %d",errno);
            return 1;
        } else {
            printf("sched_setscheduler success for %d",getpid());
        }
    }
    //test time 
       struct timeval tv;
       gettimeofday(&tv, NULL);
       unsigned long long millisecondsSinceEpoch = (unsigned long long)(tv.tv_sec) * 1000 +
                   (unsigned long long)(tv.tv_usec) / 1000;

       printf("before %llu\n", millisecondsSinceEpoch);
       int c =do_huge_work();
       printf("result is %d\n",c);
       gettimeofday(&tv, NULL);
       unsigned long long amillisecondsSinceEpoch = (unsigned long long)(tv.tv_sec) * 1000 +
                   (unsigned long long)(tv.tv_usec) / 1000;
       
       printf("after %llu\n", amillisecondsSinceEpoch- millisecondsSinceEpoch);
    /*
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

    ret = setpriority(PRIO_PROCESS,pid,-20);
    if (ret !=0) {
        printf("setpriority fail\n");
        printf("errno is %d",errno);
        return 1;
    } else {
        printf("setpriority success\n");
    }*/


    return 0;
}
 int do_huge_work()
{
    int i=0;
    int a=0;
    int b=0;
    int c=0;
    int loop = 2000000000;
    for(;i<loop;i++){
        a++;
        b++;
        c+=a*b;
        //c=a*b;
    }
    return c;
}
