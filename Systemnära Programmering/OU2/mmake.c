#include "mmake.h"


int main(int argc, char *argv[]){
    struct flags *flag = check_flags(argc, argv);
    char **cmd = get_cmd(argc, argv);
    FILE *input;
    int k = 0;
    if(flag->flag_f == true){
        if((input = fopen(flag->file_name, "r")) == NULL){
            perror(flag->file_name);
            exit(1);
        }
    }
    else{
        if((input = fopen("mmakefile", "r")) == NULL){
            perror("mmakefile");
            exit(1);
        }
    }

    makefile *made_file;
    if((made_file = parse_makefile(input)) == NULL){
        fprintf(stderr, "Could not parse desired file\n");
        exit(1);
    }
    fclose(input);
    if(cmd[k] != NULL){
        while(cmd[k] != NULL){
            build_target(made_file, cmd[k], flag);    
            k++;    
        }
    }
    else{
        build_target(made_file, makefile_default_target(made_file), flag);
    }
    
    int status;
    wait(&status);
    deallocation(cmd, flag, made_file);
    exit(0);
}



char **get_cmd(int argc, char *argv[]){
    char **cmd;
    if(argc - optind < 0){
        return NULL;
    }
    if((cmd = malloc(((argc - optind) + 1)*sizeof(char*))) == NULL){
        perror("Failed to allocate memory for commands");
        exit(1);
    }
    int i;
    for(i = optind; i < argc; i++){
        if((cmd[i - optind] = malloc((strlen(argv[i]) + 1) * sizeof(char))) == NULL){
            perror("Failed to allocate memory for individual commands");
            exit(1);
        }
        strcpy(cmd[i - optind], argv[i]);
        //printf("cmd[%d] = %s, argv[%d] = %s\n", i - optind, cmd[i - optind], i, argv[i]);
    }
    cmd[i - optind] = NULL;
    return cmd;
}

struct flags *check_flags(int argc, char *argv[]){
    struct flags *flag;
    if((flag = malloc(sizeof(struct flags))) == NULL){
        perror("Failed to allocate memory for flags");
        exit(1);
    }
    flag->flag_f = false;
    flag->flag_B = false;
    flag->flag_s = false;
    int opt;

    while((opt = getopt(argc, argv, "f:Bs")) != -1){
        switch (opt)
        {
        case 'f':
            flag->flag_f = true;
            flag->file_name = optarg;
            break;
        case 'B':
            flag->flag_B = true;
            break;
        case 's':
            flag->flag_s = true;
        default:
            break;
        }
    }
    return flag;
}

void build_target(makefile *make, const char *target_name, struct flags *flag){
    rule *target_rule;
    if(((target_rule = makefile_rule(make, target_name)) == NULL) && (access(target_name, F_OK) != 0)){
        fprintf(stderr, "No rule to make target '%s'\n", target_name);
        exit(1);
    }
    else if(target_rule == NULL){
        return;
    }
    const char** target_prereqs = rule_prereq(target_rule);
    int i = 0;
    bool exec = false;
    while(target_prereqs[i] != NULL){
        build_target(make, target_prereqs[i], flag);
        if((access(target_name, F_OK)) != 0){
            //exec_target(target_rule, flag);
            exec = true;
        }
        else if(check_if_target_should_be_built(target_prereqs[i], target_name, flag)){
            //exec_target(target_rule, flag);
            exec = true;
        }
        i++;
    }
    if(exec == true){
        exec_target(target_rule, flag);
    }
    
    return;
}

bool check_if_target_should_be_built(const char *prereq_name, const char *target_name, struct flags *flag){
    if(flag->flag_B == true){
        return true;
    }
    struct stat check_target;
    struct stat check_prereq;
    if(stat(target_name, &check_target) < 0){
        perror("Failed stat");
        exit(1);
    }
    if(stat(prereq_name, &check_prereq) < 0){
        perror("Failed stat");
        exit(1);
    }
    if(check_prereq.st_mtime > check_target.st_mtime){ 
          return true;
    }
    return false;
}


void exec_target(rule *rule, struct flags *flag){
    pid_t child;
    if((child = fork()) < 0){
        perror("Failed in forking");
        exit(1);
    }
    else if(child == 0){
        int status;
        int i = 1;
        char **rules = rule_cmd(rule);
        if(flag->flag_s == false){
            fprintf(stdout, "%s", rules[0]);
            while(rules[i] != NULL){
                fprintf(stdout, " %s", rules[i]);
                i++;
            }
            fprintf(stdout, "\n");
            fflush(stdout);
        }
        if((status = execvp(rules[0], rules)) == -1){
            perror(rules[0]);
            int exit_status = WEXITSTATUS(status);
            exit(exit_status);
        }
    }
    else{
        int status;
        waitpid(child, &status, 0);
        if(WEXITSTATUS(status) != 0){
            exit(EXIT_FAILURE);
        }
    }
}

void deallocation(char **cmd, struct flags *flag, makefile *made){
    makefile_del(made);
    free(flag);
    int i = 0;
    while(cmd[i] != NULL){
        free(cmd[i]);
        i++;
    }
}