#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define handle_error(msg) \
    do { perror(msg); sleep(10); exit(EXIT_FAILURE); } while (0)


int main(int argc, char *argv[])
{
    char *addr = 0;
    int i = 0;
    while(1 == 1) {
        addr = mmap(0, 1, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_NORESERVE|MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
        if (addr == MAP_FAILED)
          handle_error("mmap");
        i++;
        printf("Allocated map: %i, %p\n", i, addr);
    }
    exit(0);
}
