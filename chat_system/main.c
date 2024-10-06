#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {



    /*problem*/
    //when two processes acces same shared memory the order in which they will execute can result in unpredictable outcome when two processes access the same memory segment they may overwrite eachc other message or can read inconsistent data
    /*solution*/
    //to soslve this issue we must do something such that only onr processes acces the shared memory at a time
    //techniques such as locks can be used for that



    pid_t pid;
    pid = fork();
    if (pid == 0) {

        char *args[] = {"./sender", NULL};

        execvp(args[0], args);



        exit(0);

    }
    pid = fork();
    if (pid == 0) {

        char *args[] = {"./reciever", NULL};



        execvp(args[0], args);


        exit(0);
    }
    wait(NULL);
    wait(NULL);


    return 0;
}
