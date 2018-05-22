#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
    pid_t myTID;
    myTID = syscall(SYS_gettid);
    printf("Thread ID: %i\n", myTID);
    sleep(10);
    return NULL;
}
 
int main()
{
    pthread_t thread_id;
    pid_t myPID;
    myPID = getpid();
    printf("PID: %i\n", myPID);
    sleep(5);
    printf("Before Thread\n");
    int i = 0;
    while(1 == 1) {
      pthread_create(&thread_id, NULL, myThreadFun, NULL);
      if (thread_id >= 0 && i < 655360) {
        i++;
        printf("After Thread %i\n", i);
      } else {
        printf("Boom\n");
        break;
      }
    }
    exit(0);
}
