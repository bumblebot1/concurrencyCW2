#include "Sh.h"

uint8_t isNumber(char* str){
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
    int x = readLine(0,str);
    char* token = strtok(str," ");
    uint32_t args = 0;
    if(token!=NULL){
      if(strcmp(token,"fork")==0){
        token = strtok(NULL," ");
        if(token!=NULL){
          char args[strlen(token)];
          strcpy(args,token);
          if(isNumber(args)==1){
            uint32_t pid = parseInt(args);
            token = strtok(NULL," ");
            if(token==NULL){
              //execute the fork here
              pid = fork(pid,50);
              if(pid == -1){
                printf("Fork failed!Maybe you tried forking a non existing process?\n");
              }
            }
            else{
              strcpy(args,token);
              if(isNumber(args)==1){
                token = strtok(NULL," ");
                if(token==NULL){
                  uint32_t weight = parseInt(args);
                  pid = fork(pid,weight);
                  if(pid == -1){
                    printf("Fork failed!Maybe you tried forking a non existing process?\n");
                  }
                }
                else{
                  printf("Too many arguments for your fork command!\n");
                }
              }
            }
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
              int res = exit(pid);
              if(res == -1){
                printf("Exit has failed!Maybe your tried exiting a non existing process?\n");
              }
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


      else if (strcmp(token,"ps")==0){
        token = strtok(NULL," ");
        if(token!=NULL){
          printf("Too many arguments for your ps command!\n");
        }
        else{
          ps();
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
