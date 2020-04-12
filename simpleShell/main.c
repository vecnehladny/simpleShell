//
//  main.c
//  simpleShell
//
//  Created by vecnehladny on 12/04/2020.
//  Copyright © 2020 vecnehladny. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

void read_command(char cmd[], char *par[]){
    char line[1024];
    int count = 0, i = 0, j = 0;
    char *array[100], *pch;
    
    for(;;){
        int c = fgetc(stdin);
        line[count++] = (char) c;
        
        if(c == '\n') {
            break;
        }
    }
    
    if(count == 1) {
        return;
    }
    
    pch = strtok(line, " \n");
    
    while(pch != NULL) {
        array[i++] = strdup(pch);
        pch = strtok(NULL, " \n");
    }
    
    strcpy(cmd, array[0]);
    
    for(int j = 0; j < i; j++){
        par[j] = array[j];
    }
    par[i] = NULL;
}

void type_prompt(){
    char time_buffer[40];
    char username_buffer[40];
    char hostname_buffer[40];
    struct timeval time;
    gettimeofday(&time, NULL);
    strftime(time_buffer, 40, "%T", localtime(&time.tv_sec));
    getlogin_r(username_buffer, 40);
    gethostname(hostname_buffer, 40);
    
    char prompt[60];
    strcat(prompt, time_buffer);
    strcat(prompt, " ");
    strcat(prompt, username_buffer);
    strcat(prompt, "@");
    strcat(prompt, hostname_buffer);
    strcat(prompt, " > ");
    
    
    
    write(STDOUT_FILENO,prompt,strlen(prompt));
 
}

int main(int argc, const char * argv[]) {
    char cmd[100], command[100], *parameters[20];
         
    //enviroment variable
    char *envp[] = {(char *) "PATH=/bin", 0};
    
    while(1){
        type_prompt();
        read_command(command, parameters);
        
        if(fork() != 0){
            wait(NULL);
        }
        else {
            strcpy(cmd, "/bin/");
            strcat(cmd, command);
            execve(cmd, parameters, envp);
        }
        
        if(strcmp(command, "exit") == 0){
            break;
        }
    }
    
    return 0;
}
