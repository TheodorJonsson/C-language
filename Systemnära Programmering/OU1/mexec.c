#include "mexec.h"

int main(int argc, char *argv[]){
    char *input_string;
                /*  Checking arguments  */
    if(argc > 2){
        perror("Program does not accept more than one argument");
        exit(1);
    }
    else if(argc == 1){
        input_string = read_input_string(stdin);    
    }
    else if(argc == 2){
        FILE *f; 
        if((f = fopen(argv[1], "r")) == NULL){
            perror(argv[1]);
            exit(1);
        }
        input_string = read_input_string(f);
        fclose(f);
    }
    else{
        perror("Unknown Error with arguments");
        exit(1);
    }
    
                /*  Initializing variables  */
    int nr_of_strings = amount_of_strings(input_string, '\n');
    char **array_of_string = split_input_string(input_string, nr_of_strings, "\n");    
    int nr_of_pipes;
    if(nr_of_strings > 1){
        nr_of_pipes = nr_of_strings - 1;
    }
    else{
        nr_of_pipes = 1;
    }
    int pipe_array[nr_of_pipes][2];

    create_pipes(nr_of_pipes, pipe_array);
    creating_forks(array_of_string, nr_of_pipes, pipe_array, nr_of_strings, input_string);
        
        /*  Closing the pipes for the main process aswell   */
    for(int i = 0; i <= nr_of_pipes; i++){
        close(pipe_array[i][0]);
        close(pipe_array[i][1]);
    }

    
    deallocate_everything(array_of_string, input_string, nr_of_strings);
    int status;
    for(int i = 0; i < nr_of_strings; i++){
        wait(&status);
        if(WEXITSTATUS(status) != 0){
            exit(EXIT_FAILURE);
        }
    }
    exit(0);
}


char *read_input_string(FILE *inputstream){
    int n = 8, i = 0;
    char *input_string;
    if((input_string = malloc(n*sizeof(char))) == NULL){
        perror("Failed to allocate memory for string");
        exit(1);
    }
    char p = 1;

    while(p != EOF){
        p = fgetc(inputstream);
        input_string[i] = p;
        i++;
        if(i == n - 1){
            n *= 2;
            if((input_string = realloc(input_string, n)) == NULL){
                perror("Failed to realloc memory for string");
                exit(1);
            }
        }
    }
    if(input_string[i-2] == '\n'){
        input_string[i-2] = '\0';   
    }
    else{
        input_string[i-1] = '\0';
    }
    if(i <= 0){
        perror("Not enough commands from input");
        exit(1);
    }
    return input_string;
}


int amount_of_strings(char *input_string, char counting_character){
    int nr_of_strings = 0, i = 0;
    while(input_string[i] != '\0'){
        if(input_string[i] == counting_character){
            nr_of_strings++;
        }
        i++;
    }
    if(input_string[i] == '\0'){
        nr_of_strings++;
    }
    return nr_of_strings;
}


char **split_input_string(char *input_string, int nr_of_string, char* splitting_character){
    char **splitting_string;
    if((splitting_string = malloc((nr_of_string + 1)*sizeof(char*))) == NULL){
        perror("Failed in allocating memory for array of strings");
        exit(1);
    }
    int i = 0;
    char *temp;
    temp = strtok(input_string, splitting_character);

    while(temp != NULL){
        if((splitting_string[i] = malloc((strlen(temp) + 1)*sizeof(char))) == NULL){
            perror("Failed in allocating memory for individual strings");
            exit(1);
        }
        splitting_string[i] = strcpy(splitting_string[i], temp);
        temp = strtok(NULL, splitting_character);
        i++;
    }
    splitting_string[i] = NULL;
    
    return splitting_string;
}


void create_pipes(int nr_of_pipes, int pipe_array[nr_of_pipes][2]){
    for(int i = 0; i <= nr_of_pipes; i++){
        pipe(pipe_array[i]);
    }
}


void creating_forks(char **input_string, int nr_of_pipes, int pipe_array[nr_of_pipes][2],  int nr_of_strings, char *input_from_file){
    pid_t child;
    int nr_of_child = 0; 
    while(nr_of_child < nr_of_strings){
        if((child = fork()) < 0){
            perror("Failed in creating a fork");
            exit(1);
        }
        else if(child == 0){
            connecting_pipes_and_exec(nr_of_child, input_string, nr_of_pipes, pipe_array, nr_of_strings, input_from_file);    
        }   
        nr_of_child++;
    }
}


void connecting_pipes_and_exec(int nr_of_child, char **input_string, int nr_of_pipes, int pipe_array[nr_of_pipes][2], int nr_of_strings, char *input_from_file){
        /*  Splits the input string at index of the current child   */
        /*  and creates a new string array to be used in exec       */
    char delim[] = "\x20"; // character used for knowing where to split the string in this case \x20 equals just a space
    int amount = amount_of_strings(input_string[nr_of_child], '\x20');
    char **splitted = split_input_string(input_string[nr_of_child], amount, delim);

        /*  Dupping the pipes first child   */
    if(nr_of_child == 0){
        if(nr_of_strings != 1){
            dup2(pipe_array[nr_of_child][1], STDOUT_FILENO);
        }       
    }
        /* Dupping the pipes for the last child     */
    else if(nr_of_child == (nr_of_strings - 1)){
        dup2(pipe_array[nr_of_child - 1][0], STDIN_FILENO);
    }
    else{
        /* Dupping the pipes for the middle child/children  */
        dup2(pipe_array[nr_of_child - 1][0], STDIN_FILENO);
        dup2(pipe_array[nr_of_child][1], STDOUT_FILENO);
    }
        /* Closing the pipes after the dupping has been done    */
    for(int i = 0; i <= nr_of_pipes; i++){
        close(pipe_array[i][0]);
        close(pipe_array[i][1]);
    }
    int status;
    if((status = execvp(splitted[0], splitted)) == -1){
        deallocate_everything(input_string, input_from_file, nr_of_strings);
        perror(splitted[0]);
        for(int i = 0; i < amount; i++){
            free(splitted[i]);
        }
        free(splitted);
        int exit_status = WEXITSTATUS(status);
        //printf("Exit number %d\n", status);

        exit(exit_status);
    }
}




void deallocate_everything(char **input_string, char *input_from_file, int nr_of_strings){
    for(int i = 0; i <= nr_of_strings; i++){
        free(input_string[i]);
    }
    free(input_string);
    free(input_from_file);
}