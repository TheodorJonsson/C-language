#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <time.h>

static int g = 0;

int main(int argc, char* argv[]){
    int var = 0;
    pid_t ret;

    while(++var < 4){
        if(ret = fork()) < 0){
            perror("fork error");
            exit(1);
        }
        else if(ret == 0){
            g++;
        }
        else{
            var++;
            g+=2;
            if(waitpid(ret, NULL, 0) != ret){
                perror("waitpid error");
                exit(1);
            }
        }
    }
    printf("mypid = %d parentpid = %d ret = %d var %d g = %d\n", getpid(), getppid(), ret, var, g);
    exit(0);
}