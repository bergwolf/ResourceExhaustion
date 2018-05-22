#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define handle_error(msg) \
    do { perror(msg); sleep(10); exit(EXIT_FAILURE); } while (0)


int main(int argc, char *argv[])
{
    char *addr = 0;
    int i = 0;
    pid_t mypid = getpid();
    char myprefix[26];
    snprintf(myprefix, 26, "c_mmap_pid_%i_XXXXXX", mypid);
    int fd = mkstemp(myprefix);
    if (fd < 0)
      handle_error("open");
    while(1 == 1) {
        /* mmaping a file triggers vm.max_map_count */
        addr = mmap(0, 1, PROT_READ|PROT_WRITE|PROT_EXEC,
            MAP_NORESERVE|MAP_PRIVATE, fd, 0);
        if (addr == MAP_FAILED)
          handle_error("mmap");
        /* Can mmap and mprotect as many anonymous maps as one wants
         * addr = mmap(0, 1, PROT_READ|PROT_WRITE|PROT_EXEC,
         *     MAP_NORESERVE|MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
         * if (addr == MAP_FAILED)
         *   handle_error("mmap");
         * if (0 != mprotect(addr, 1, PROT_READ|PROT_WRITE|PROT_EXEC))
         *   handle_error("mprotect");
         */
        i++;
        printf("%i: Allocated map: %i, %p\n", mypid, i, addr);
    }
    exit(0);
}
