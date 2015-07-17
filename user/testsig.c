#include <unistd.h>
#include <sprintf.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <lru.h>
#include <stat.h>
#include <sos/signal.h>

static volatile int quit = 0;
static void signal_handler(int sig)
{
    pid_t pid = getpid();
    quit = 1;
    printf("%s: pid %d, sig %d\n", __func__, pid, sig);
}

int main(int argc, char *argv[])
{
    signal(SIGUSR1, (uint32_t)signal_handler);
    pid_t pid = fork();
    if (pid == 0) {
        printf("child(%d): busy loop\n", getpid());
        int count = 0;
        while (!quit) {
            int r = 0;
            for (int i = 0; i < 100000; i++) {
                for (int j = 0; j < 65000; j++) {
                    r += i*j;
                }
            }
            /*sleep(10);*/
            printf("loop %d %d\n", r, count++);
        }

    } else if (pid > 0) {
        kill(pid, SIGUSR1);
        wait();
        printf("parent(%d) quit\n", getpid());
    }

    return 0;
}