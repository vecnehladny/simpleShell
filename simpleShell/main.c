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
#include <unistd.h>
#include <string.h>

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
