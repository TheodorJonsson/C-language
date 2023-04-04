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

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("too few arguments");
    }
    char **cmd = malloc((argc - 2) * sizeof(char*));
    char **files = malloc(2*sizeof(char*));
    int opt;
    int n = 0;
    int k = 0;
    for(int i = 0; i < argc; i++){
        if(access(argv[i], X_OK) == 0){
            files[n] = malloc(strlen(argv[i] + 1) * sizeof(char));
            strcpy(files[n], argv[i]);
            n++;
        }
        else{
            cmd[k] = malloc(strlen(argv[i] + 1) * sizeof(char));
            strcpy(cmd[k], argv[i]);
            k++;
        }       
    }
    cmd[k] = NULL;
    files[n] = NULL;

    int j = 0;
    int status;
    pid_t ret;

    while(j < k){
        if((ret = fork()) < 0){
            perror("fork error");
            exit(1);
        }
        else if(ret == 0){
            printf("executing command %s in cmd[%d] and files\n", cmd[j]); //if((status = execvp(cmd[j], files)) == -1){perror("exec failed"); exit(1);} 
        }
        else{
            if(waitpid(ret, NULL, 0) != ret){
                perror("waitpid error");
                exit(1);
            }
        }
        j++;
    }

    return 0;
}
