#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256
#define MAX_FIELDS 5 /* 5 fields: views,user,upload_time,duration,title */
int cnt=0;
struct clip *build_a_lst();
struct clip *append();
//int find_length();
void print_a_lst();
void split_line();
struct clip {
  int views;
  char *user;
  char *upload_time;
  char *duration;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  int n;
  head = build_a_lst(*(argv+1));
  //n = find_length(head);
  n=cnt;
  printf("%d clips\n",n);
  print_a_lst(head);		/* prints the table */
  return 0;
}

struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp;
  char *fields[MAX_FIELDS];
  char line[LINE_LENGTH];
  //int cnt=0;
  hp=NULL;
  fp=fopen(fn, "r"); // open fn
  if (fp== NULL){
    printf("Unable to open file");
  }
  while(fgets(line,LINE_LENGTH,fp) != NULL){ // while no more lines
    //printf("%s", line); // read a line
    split_line(fields, line); // split the line into five substrings/int and store them in a struct
    hp=append(hp, fields);  // append - add the struct at the end of the list
    cnt++;
  } 
  return hp; // return the head pointer holding the list
}
/* fields will have five values stored upon return */
void split_line(char **fields,char *line) {
  int i=0;
  char *token, *delim;
  delim = ",\n";
  token=strtok(line,delim);
 // fields[i]=token;
  while (token != NULL && i<5){ //repeat until strtok returns NULL using strtok(NULL, delim);
    fields[i]=token;
    i++;
    token = strtok(NULL, delim); //call strtok(line, delim);
  }
}

/* set five values into a clip, insert a clip at the of the list */
struct clip *append(struct clip *hp,char **five) {
  struct clip *cp,*tp;
  tp=malloc(sizeof(struct clip));// malloc tp
  //malloc for five strings
  tp->title=(char*)malloc(strlen(five[0]+1)*sizeof(char));
  tp->user=(char*)malloc(strlen(five[1]+1)*sizeof(char));
  tp->upload_time=(char*)malloc(strlen(five[2]+1)*sizeof(char));
  tp->duration=(char*)malloc(strlen(five[3]+1)*sizeof(char));
  tp->views=atoi(five[4]);
  strcpy(tp->title, five[0]); //strcpy five strings to tp
  strcpy(tp->user, five[1]);
  strcpy(tp->upload_time, five[2]);
  strcpy(tp->duration, five[3]);
  tp->next=NULL;
  if(hp == NULL){
    hp=tp;
  }
  else{
    cp=hp;
    while(cp->next != NULL){ //use cp to traverse the list
      cp=cp->next; 
    }
    cp->next=tp; //insert tp at the end of the list pointed by hp
  }
  return hp;
}

void print_a_lst(struct clip *cp) {
    while(cp != NULL) { //use a while loop and the statement below to print the list
     printf("%s, %s, %s, %s, %d\n",cp->title, cp->user, cp->upload_time, cp->duration, cp->views);
     cp=cp->next;
  }
}