#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    printf("ЩЕМАНА\n");
    fflush(stdout);
    
    pid_t pid;
    int i;
    
    for (i = 1; i <= 500; i++) {
        pid = fork();
        
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) {
            char process_name[20];
            snprintf(process_name, sizeof(process_name), "ЩЕМАНА-%d", i);
            
            pid_t child_pid = getpid();
            
            printf("PID: %d, Name: %s\n", child_pid, process_name);
            fflush(stdout);
            
            exit(EXIT_SUCCESS);
        }
    }
    
    for (i = 1; i <= 500; i++) {
        wait(NULL);
    }
    
    return 0;
}
