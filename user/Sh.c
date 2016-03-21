#include "Sh.h"

void Sh() {
  char str[1000];
  while( 1 ) {
    int x = readLine(0,str);
    char* token = strtok(str," ");
    if(token!=NULL){
      printf(token);
      printf("\n");
      if(strncmp(token,"fork",4)==0){
        while(token!=NULL){
          token = strtok(NULL," ");
          //parse the id of the process to be forked
          //if int the call fork(id) and do the fork
          //else invalid command
        }
        printf("\n fork branch\n");
      }
      else if (strncmp(token,"exit",4)==0){
        while(token!=NULL){
          token = strtok(NULL," ");
          //parse the id of the process to be forked
          //if int then call exit(id) and close the process
          //else invalid command
        }
        printf("\n exit branch \n");
      }
      else if (strncmp(token,"exec",4)==0){
        while(token!=NULL){
          token = strtok(NULL," ");
          //parse the id of the process to be executed
          //if int then call exec(id) and schedule the process
          //else invalid command
        }
        printf("\n exit branch \n");
      }
    }
    printf(" %d\n",strlen(str));
  }
}

void (*entry_Sh)() = &Sh;
