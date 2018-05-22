#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define handle_error(msg) \
    do { perror(msg); sleep(10); exit(EXIT_FAILURE); } while (0)

// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *i)
{
    pid_t myTID = syscall(SYS_gettid);
    pid_t myPID = getpid();
    printf("%i: In Thread ID: %i, %i\n", myPID, *(int *)i, myTID);
    if (i != NULL)
      free(i);
    sleep(10);
    return NULL;
}
 
int main()
{
    pid_t myPID = getpid();
    int i = 0;
    int *arg = NULL;
    pthread_t thread_id;
    pthread_attr_t tattr;

    printf("PID: %i\n", myPID);
    sleep(5);
    printf("%i: Before Thread\n", myPID);

    if (0 != pthread_attr_init(&tattr))
      handle_error("pthread_attr_init");
    if (0 != pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED))
      handle_error("pthread_attr_init");

    while(1 == 1) {
      // pass in which iteration this is
      arg = malloc(sizeof(*arg));
      if (arg == NULL) {
        handle_error("malloc");
      }
      *arg = i;

      pthread_create(&thread_id, &tattr, myThreadFun, arg);
      if (thread_id >= 0 && i < 655360) {
        i++;
        printf("%i: After Thread Create %i\n", myPID, i);
      } else {
        printf("%i: Boom: %i\n", myPID, i);
        break;
      }
    }

    exit(0);
}
