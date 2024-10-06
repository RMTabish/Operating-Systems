#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
//library for shared memory 
#include<sys/shm.h>

int main(){

    printf("prgram started");
//store the adress of shared segment 
void *shm_ad;

//stores the mesage of user 
char buf[100];

//STORS THE ID OF sharedmemory
int id;
//creating the shared memory 
//permission given to user group and others by 0666
id=shmget((key_t)6969,1024,0666|IPC_CREAT);

printf("shared memory key is %d\n",id);

//attching the process to sharedmemory 
shm_ad=shmat(id,NULL,0);
printf("process attasched to %p\n",shm_ad);

//printf("process is sccesfully attached at ",shm_ad);
printf("enter the message\n");

//take input
read(0,buf,100);
//writing entered message to shared memory
strcpy(shm_ad,buf);



 



}
