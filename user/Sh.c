#include "Sh.h"

int isNumber(char* str){
  for(int i = 0; i <= strlen(str); i++){
    if( str[i] =='\0' )
      return 1;
    if( str[i]-'0'< 0 || str[i]-'0' > 9)
      return 0;
  }
  return 1;
}

int parseInt(char* str){
  int num = 0;
  for(int i = 0; i <= strlen(str); i++ ){
    if(str[i]!='\0'){
      int val = str[i]-'0';
      num = num*10 + val;
    }
  }
  return num;
}

void Sh() {
  while( 1 ) {
    char str[1000];
    int x = readLine(0,str);
    char* token = strtok(str," ");
    int args = 0;
    if(token!=NULL){
      if(strcmp(token,"fork")==0){
        token = strtok(NULL," ");
        if(token!=NULL){
          char args[strlen(token)];
          strcpy(args,token);
          if(isNumber(args)==1){
            token = strtok(NULL," ");
            if(token==NULL){
              //execute the fork here
              int pid = parseInt(args);
              fork(pid);
            }
            else
              printf("Too many arguments for your fork command!\n");
          }
          else{
            printf("The pid you gave in your fork is not a number!\n");
          }
        }
        else{
          printf("Not enough arguments for the fork!Please Enter a process id!\n");
        }
      }


      else if (strcmp(token,"exit")==0){
        token = strtok(NULL," ");
        if(token!=NULL){
          char args[strlen(token)];
          strcpy(args,token);
          if(isNumber(args)==1){
            token = strtok(NULL," ");
            if(token==NULL){
              //execute the exit here
              int pid = parseInt(args);
              printf("%d\n",pid);
              //exit(pid)
            }
            else
              printf("Too many arguments for your exit command!\n");
          }
          else{
            printf("The pid you gave in your exit is not a number!\n");
          }
        }
        else{
          printf("Not enough arguments for the exit!Please Enter a process id!\n");
        }
      }


      else if (strcmp(token,"exec")==0){
        token = strtok(NULL," ");
        if(token!=NULL){
          char args[strlen(token)];
          strcpy(args,token);
          if(isNumber(args)==1){
            token = strtok(NULL," ");
            if(token==NULL){
              //execute the exec here
              int pid = parseInt(args);
              printf("%d\n",pid);
              //exec(pid)
            }
            else
              printf("Too many arguments for your exec command!\n");
          }
          else{
            printf("The pid you gave in your exec is not a number!\n");
          }
        }
        else{
          printf("Not enough arguments for the exec!Please Enter a process id!\n");
        }
      }


      else{
        printf("Your command has a wrong name!\n");
      }


    }
    else{
      printf("\n");
    }
  }
}

void (*entry_Sh)() = &Sh;
