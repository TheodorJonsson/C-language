#include "util.h"

/*TaskQueue *if_no_args(TaskQueue *taskPool);*/
/*function used to remove task only used when deallocating the TaskQueue struct*/
struct task *remove_Task(struct task *task);

struct task *create_Task(char *file_name, int dirID){
    struct task *task = safe_malloc(sizeof(struct task));

    task->file_name = safe_malloc(strlen(file_name) + 1);
    strcpy(task->file_name, file_name);
    free(file_name);
    task->dirID = dirID;
    return task;
}

taskList *create_TaskList(void){
    taskList *list = safe_malloc(sizeof(taskList));
    list->task_head = safe_malloc(sizeof(struct task));
    list->task_head->file_name = NULL;
    list->task_head->dirID = 0;
    list->task_head->next = list->task_head;
    list->task_head->prev = list->task_head;

    return list;
}

struct task *first_Task(taskList *tsk_lst){
    return tsk_lst->task_head->next;       
}

struct task *next_Task(struct task *tsk_lst){
    return tsk_lst->next;
}

struct task *last_Task(taskList *tsk_lst){
    return tsk_lst->task_head;
}

struct task *dequeue_Task(TaskQueue *taskPool){
    struct task *task = first_Task(taskPool->task_head);

    struct task *before = task->prev;
    struct task *after = task->next;

    before->next = after;
    after->prev = before;
    return task;
}

void enqueue_Task(int dirID, char *file_name, TaskQueue *taskPool){

    struct task *end = last_Task(taskPool->task_head);
    struct task *task = create_Task(file_name, dirID);

    struct task *before = end->prev;
    struct task *after = end;


    task->next = after;
    after->prev = task;

    task->prev = before;
    before->next = task;
    //printf("TASK = %s\n", task->file_name);

}

struct task *remove_Task(struct task *task){
    struct task *before = task->prev;
    struct task *after = task->next;

    before->next = after;
    after->prev = before;

    free(task->file_name);
    free(task);

    task = after;

    return task;
}


bool task_equal(struct task *task1, struct task *task2){
    if(task1 == task2){
        return true;
    }
    return false;
}

bool taskList_is_empty(taskList *task_list){
    if(task_list->task_head->next == task_list->task_head){
        return true;
    }
    return false;
}

TaskQueue *init_TaskQueue(void){
    TaskQueue *taskPool = safe_malloc(sizeof(TaskQueue));
    taskPool->amount_of_dir = 0;
    taskPool->finished = false;
    taskPool->task_head = create_TaskList();
    taskPool->curr_task = first_Task(taskPool->task_head);
    taskPool->success = 0;
    return taskPool;
}

Directory *insert_Directory(char *directory_name, int ID){
    Directory *dir = safe_malloc(sizeof(Directory));
    dir->directoryName = safe_malloc(strlen(directory_name) + 1);
    strcpy(dir->directoryName, directory_name);
    dir->ID = ID;
    dir->sum = 0;

    return dir;
}


TaskQueue *get_tasks(int argc, char *argv[]){
    TaskQueue *taskPool = init_TaskQueue();
    //printf("%d\n", taskPool->success);
    taskPool->dir = safe_malloc(((argc - optind) + 1)*sizeof(Directory*));
    int i;
    for(i = optind; i < argc; i++){
        int pos = i - optind;
        char *str = safe_malloc(strlen(argv[i]) + 1);
        strcpy(str, argv[i]);
        enqueue_Task(pos, str, taskPool);
        taskPool->dir[pos] = insert_Directory(argv[i], pos);
        taskPool->amount_of_dir++;
        
    }
    taskPool->dir[i - optind] = NULL;
    //taskPool = if_no_args(taskPool);
    return taskPool;
}
/*
TaskQueue *if_no_args(TaskQueue *taskPool){
    if(taskPool->amount_of_tasks == 0){
        taskPool->dir[0] = insert_Directory(".", 0);
        enqueue_Task(0, ".", taskPool);
        taskPool->amount_of_tasks++;
    }
    return taskPool;
}*/

int check_flag(int argc, char *argv[]){
    int jflag = 1;
    int opt;
    while((opt = getopt(argc, argv, "j:")) != -1){
        switch (opt)
        {
        case 'j':
            jflag = atoi(optarg);
            break;
        default:
            break;
        }
    }
    return jflag;
}

void *safe_malloc(size_t size){
    void *allocate_mem = malloc(size);
    if(allocate_mem == NULL){
        perror("Failed to allocate memory");
        exit(1);
    }
    return allocate_mem;
}

void destroy_TaskQueue(TaskQueue *taskPool){
    while(taskList_is_empty(taskPool->task_head) == false){
        taskPool->curr_task = remove_Task(taskPool->curr_task);
    }
    int i = 0;
    while(taskPool->dir[i] != NULL){
        destroy_Dir(taskPool->dir[i]);
        i++;
    }
    free(taskPool->dir);
    free(taskPool->task_head->task_head);
    free(taskPool->task_head);
    free(taskPool);
}
void destroy_Task(struct task *tsk_lst_pos){
    free(tsk_lst_pos->file_name);
    free(tsk_lst_pos);
}

void destroy_Dir(Directory *dir){
    free(dir->directoryName);
    free(dir);
}