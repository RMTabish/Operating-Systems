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
shm_ad=shmat(id,NULL,0);
printf("process attasched to %p\n",shm_ad);
printf("data read is : %s\n",(char *)shm_ad);



}
