#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
# include<stdlib.h>
# include<unistd.h>
#include<sys/wait.h>

using namespace std;
int main(){


//makign of the number n
int a= rand() % 90 + 10;
a*=1;
//cout<<a;

int y=2541/a;
//cout<<y;
y=y%25;



if(y<25){
    y+=25;

}




//storing sum of each process adn resultant matrix 
int multi=0;
int EndMat[y][y];


//making the matrix and populating it randomly
int mat[y][y];
for(int i=0;i<y;i++){
    for(int j=0;j<y;j++){
        mat[i][j]=rand() % 10 + 1;

    }
}

//writing matrix in txt file 
ofstream file;
ofstream row;

file.open("matrix.txt");

for(int i=0;i<y;i++){
    for(int j=0;j<y;j++){
        file<<mat[i][j]<<" ";//=rand();
        
    }
    file<<endl;

}

//creating n proccess;
 for(int i =0 ;i<y;i++){


     pid_t id=fork();
     if(id<0){
         cout<<"procces "<<i<<" isnt created "<<endl;
         return 0;
     
     }else if(id==0){
     
     //we in the child process 
     for(int a=0;a<y;a++){
         multi=0;
     
         for(int b=0;b<y;b++){
     multi =multi +(mat[i][b]*mat[b][a]);
         }

           // ofstream("row"+to_string(i)+".txt");


         EndMat[i][a]=multi;

     
     }
     //writing whole row in the text file

       row.open("row"+to_string(i)+".txt",ios::out);


for(int b=0;b<y;b++){

         row<< EndMat[i][b]<<" ";

}

row.close();
cout<<endl;

     exit(0);



 } 

}
for(int i =0;i<y;i++){
    wait(NULL);

}

fstream re;
for(int p=0;p<y;p++){
       re.open("row"+to_string(p)+".txt",ios::in);
       string l;
       while(getline(re,l)){
           cout<<l<<endl;

    }
    re.close();

}


    return 0;
    }
