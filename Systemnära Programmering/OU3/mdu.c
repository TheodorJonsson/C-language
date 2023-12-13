#include "mdu.h"

#define BUFFSIZE 256


int main(int argc, char *argv[]){
    int thread_count = check_flag(argc, argv);
    if((optind - argc) == 0){
        fprintf(stderr, "not enough arguments\n");
        exit(1);
    }
    TaskQueue *taskPool = get_tasks(argc, argv);
    
    pthread_t threads[thread_count];
    pthread_mutex_init(&taskPool->mutexQue, NULL);
    pthread_cond_init(&taskPool->condQue, NULL);
    for(int i = 0; i < thread_count; i++){
        if(pthread_create(&threads[i], NULL, &startThread, (void *) taskPool) != 0){
            perror("Failed in creating thread");
        }
    }
    for(int i = 0; i < thread_count; i++){
        if(pthread_join(threads[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }
    pthread_cond_destroy(&taskPool->condQue);
    pthread_mutex_destroy(&taskPool->mutexQue);

    for(int i = 0; i < taskPool->amount_of_dir; i++){
        printf("%ld\t%s\n", taskPool->dir[i]->sum, taskPool->dir[i]->directoryName);
    }
    int exit_code = taskPool->success;
    destroy_TaskQueue(taskPool);
    exit(exit_code);
    
}

void *startThread(void *args){
    TaskQueue *taskPool = (TaskQueue*)args;
    while(true){
        pthread_mutex_lock(&taskPool->mutexQue);
        /* Check if the queue is empty or not and if all tasks are finished */
        while(taskList_is_empty(taskPool->task_head)){
            if(taskPool->finished == true){
                pthread_cond_broadcast(&taskPool->condQue);
                pthread_mutex_unlock(&taskPool->mutexQue);
                return NULL;
            }
            else{
                pthread_cond_wait(&taskPool->condQue, &taskPool->mutexQue);
            }
        }
        /* Pick out a task from the queue*/
        struct task *task;
        if(taskList_is_empty(taskPool->task_head) == false){
            task = dequeue_Task(taskPool);
        }
        pthread_mutex_unlock(&taskPool->mutexQue);
        /* If it's a file send it to be summed up */
        if(check_if_file_or_dir(task->file_name) == true){
            executeTask(task, taskPool->dir[task->dirID], taskPool);
            pthread_mutex_lock(&taskPool->mutexQue);
            if(taskList_is_empty(taskPool->task_head) == true){
                taskPool->finished = true;
                pthread_cond_broadcast(&taskPool->condQue);
            }
            pthread_mutex_unlock(&taskPool->mutexQue);
        }
        /* If it's a directory send it to be looked through */
        else if(check_if_file_or_dir(task->file_name) == false){
            submitDirectory(taskPool, task);
        }
        else{
            fprintf(stderr, "Could not read file: %s\n", task->file_name);
        }
    }   
}       

void executeTask(struct task *task, Directory *dir, TaskQueue *taskPool){
    long int size = count_file(task->file_name);
    pthread_mutex_lock(&taskPool->mutexQue);
    dir->sum += size;
    destroy_Task(task);
    pthread_mutex_unlock(&taskPool->mutexQue);
}

long int count_file(char *file_name){
    struct stat stat;
    lstat(file_name, &stat);
    return stat.st_blocks;
}

void submitDirectory(TaskQueue *taskPool, struct task *taskDir){
    DIR *d;
    struct dirent *dir;
    /*If the directory is unreadable send the task to be summed up*/
    if((d = opendir(taskDir->file_name)) == NULL){
        fprintf(stderr, "cannot read directory '%s': Permission denied\n", taskDir->file_name);
        executeTask(taskDir, taskPool->dir[taskDir->dirID], taskPool);
        pthread_mutex_lock(&taskPool->mutexQue);
        if(taskList_is_empty(taskPool->task_head) == true){
                taskPool->finished = true;
                pthread_cond_broadcast(&taskPool->condQue);
        }
        taskPool->success = 1;
        pthread_mutex_unlock(&taskPool->mutexQue);
        return;
    }
    while((dir = readdir(d)) != NULL){
        char *file_name = concat_dir_file(taskDir->file_name, dir->d_name);
        /* if it's the current directory send it to be summed up*/
        if((!strcmp(dir->d_name, ".")) && (strcmp(dir->d_name, ".."))){
            pthread_mutex_lock(&taskPool->mutexQue);
            long int size = count_file(file_name);
            taskPool->dir[taskDir->dirID]->sum += size;
            pthread_mutex_unlock(&taskPool->mutexQue);
            free(file_name);
        }
        /* If it's a new directory send it to the queue */
        else if(check_if_file_or_dir(file_name) == false && strcmp(dir->d_name, "..")){
            pthread_mutex_lock(&taskPool->mutexQue);
            enqueue_Task(taskDir->dirID, file_name, taskPool);
            taskPool->finished = false;
            pthread_cond_broadcast(&taskPool->condQue);
            pthread_mutex_unlock(&taskPool->mutexQue);      
        }
        /* If it's a file send it to be summed up */
        else if(check_if_file_or_dir(file_name) == true && strcmp(dir->d_name, "..")){
            executeTask(create_Task(file_name, taskDir->dirID), taskPool->dir[taskDir->dirID], taskPool);
            pthread_mutex_lock(&taskPool->mutexQue);
            if(taskList_is_empty(taskPool->task_head) == true){
                taskPool->finished = true;
            }
            pthread_mutex_unlock(&taskPool->mutexQue);
        }
        else{
            free(file_name);
        }
    }
    destroy_Task(taskDir);
    closedir(d);
}

char *concat_dir_file(char *taskDir_name, char *file_name){
    char temp[BUFFSIZE] = {0};
    strcat(temp, taskDir_name);
    strcat(temp, "/");
    strcat(temp, file_name);

    char *tempallo = safe_malloc(strlen(temp) + 1);
    strcpy(tempallo, temp);
    return tempallo;
}


int check_if_file_or_dir(char *file_name){
    if(file_name == NULL){
        return -1;
    }
    struct stat task_stat;
    int check;
    check = lstat(file_name, &task_stat);
    if(check != 0){
        fprintf(stderr, "%s %s %s", "stat failed on", file_name, " \n");
        return -1;
    }
    else if(S_ISDIR(task_stat.st_mode) != 0){
        return false;
    }
    return true;
}

