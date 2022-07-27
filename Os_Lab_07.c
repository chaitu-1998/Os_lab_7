#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#define LINESIZE 1024
char * temp[10];


int main(int argc, char* argv[]) {
  char* eletempment[10];
  char* absele[10];
  char line[LINESIZE];
  int i, tempabc;
  char new_str[1000];
  FILE *ftemppnt = fopen("input.txt", "r");
    
  if(ftemppnt == NULL){
    printf("Error reading input file input.txt\n");
    exit (-1);
  }
  
  tempabc = 0;
  while (fgets(line, LINESIZE, ftemppnt) != NULL){
    eletempment[tempabc] = strdup(line);
    absele[tempabc] = strdup(line);
    tempabc++;
  }
  fclose(ftemppnt);
  time_t start;
  time_t finish;
  
  for(i = 0; i < 4; i++){
    pid_t pid;
    int update, tempabc=0;
    char* arrlistitem;
    char delim[] = " ";
    arrlistitem = eletempment[i];    
    int init_size;
    init_size = strlen(arrlistitem);
    
    char *temppnt;
    
    temppnt = strtok(arrlistitem, delim);
    temppnt = strtok(arrlistitem, "\n");
    while (temppnt != NULL){
      temp[tempabc] = strdup(temppnt);
      temppnt = strtok(NULL, delim);
      tempabc++;
    }
    
    pid = fork();
      
    if (pid > 0) {
      time(&start);
      sleep(2);
      wait(&update);
      time(&finish);
      strcat(new_str, absele[i]);
      strcat(new_str, " ");
      strcat(new_str, ctime(&start));
      strcat(new_str, " ");
      strcat(new_str, ctime(&finish));
  
      if (WIFEXITED(update)) {
        printf("Child process exited with update = %d\n", WEXITSTATUS(update));
      }
      else {
        printf("Child process did not terminate normally!\n");
      }
    }
      
    else {
      perror("fork");
      exit(EXIT_FAILURE);
    }
  }
  FILE *tempfile = fopen("output.log", "wb");
  fprintf(tempfile, "%s", new_str);
  fclose(tempfile);
}