#include "Sh.h"

uint32_t isNumber(char* str){
  for(uint32_t i = 0; i <= strlen(str); i++){
    if( str[i] =='\0' )
      return 1;
    if( str[i]-'0'< 0 || str[i]-'0' > 9)
      return 0;
  }
  return 1;
}

uint32_t parseInt(char* str){
  uint32_t num = 0;
  for(uint32_t i = 0; i <= strlen(str); i++ ){
    if(str[i]!='\0'){
      uint32_t val = str[i]-'0';
      num = num*10 + val;
    }
  }
  return num;
}

void Sh() {
  while( 1 ) {
    char str[1000];
    printf("$ ");
    uint32_t x = readLine(0,str);
    char* token = strtok(str," ");
    uint32_t args = 0;
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
              uint32_t pid = parseInt(args);
              pid = fork(pid);
              printf("%d\n",pid);
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
              uint32_t pid = parseInt(args);
              printf("%d",pid);
              exit(pid);
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
              uint32_t pid = parseInt(args);
              printf("%d",pid);
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
