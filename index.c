/* The following program gets a file name when the program is executed. It checks the validity of the input in: amount (only 1 argument), is the argument is a file, can the * program read the file. It will then parse the file and register each word and in which line it appears in a lexicographic order into an index in the form of a linked list. * Finally, it will print the index it created and free all allocated memory and open files. We are assuming each word is seperated by a white space.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 2058 /*Buffer for dynamic memory*/

/*Defining the elements of a linked list*/
typedef struct node* ptr;
typedef struct node {
  char* str;
  int* lines;
  int counter;
  ptr next;
} item;

void add2list (ptr *hptr, char* newStr, int newLine);
void freelist(ptr * hptr);
void init_item(ptr newItem);
void print_list(ptr h);

/*The following function gets a file name when the program is executed. It checks the validity of the input in: amount (only 1 argument), is the argument is a file, can the program read the file. It will then parse the file and register each word and which line it appears in. Finally, it will print the index it created.
* argc Counter for arguments recieved
* argv The arguments recieved
* returns: 0 if successful*/
int main (int argc, char* argv[]) {
  ptr h = NULL;
  FILE *fd;
  char* curStr = malloc(sizeof(char)*BUFFER);
  char* curLine = malloc(sizeof(char)*BUFFER);
  int curLineNum = 1;
  int state;
  int counter = 1;
  
  if(curStr==NULL) {
    printf("\nCannot allocate memory\n");
    exit(0);
  }
  
  /*Check validity of input in amount (only 1 file)*/
  if (argc>2) {
    printf("\nYou entered too many arguments\n");
    exit(0);
  }

  else if (argc<2) {
    printf("\nYou didn't enter a file to be read\n");
    exit(0);
  }
  
  /*Check validity of input, is the argument is a file, can the program read the file*/
  if (!(fd = fopen(argv[1], "r"))) {
    printf("\nCannot open file\n");
    exit(0);
  }
  
  while((state = fscanf(fd, "%[^\n]", curLine)) != -1) { /*Parse the file line by line*/
    if(state==0) { /*Handle big strings*/
      counter++;
      rewind(fd);
      curLine = realloc(curLine, strlen(curLine)*sizeof(char)*counter);
      if(curLine==NULL) {
        printf("\nCannot allocate memory\n");
        exit(0);
      }
      curStr = realloc(curStr, strlen(curLine)*sizeof(char));
      if(curStr==NULL) {
        printf("\nCannot allocate memory\n");
        exit(0);
      }
    }
      
    if (strcmp(curLine, "\n") == 0) continue; /*Check for empty line*/
    /*Parse the current line word by word*/
    curStr = strtok(curLine, " \t");
    while(curStr != NULL) {
      add2list(&h, curStr, curLineNum);
      curStr = strtok(NULL, " \t");
    }
    fgetc(fd);
    curLineNum++;
  }
  
  print_list(h); /*Print which words appear in which lines*/
  
  /*Free allocated memory and close the open file*/
  freelist(&h);
  if(fclose(fd) != 0) printf("\nCouldn't close file\n"); /*Check if closing the file was successful*/
  free(curStr);
  free(curLine);
  
  return 0;
}

/*The following function adds a string to a linked list in a lexicographic order and registers which line it appeared in
* *hptr: The head of the linked list that's being modified
* newStr: The string value of the item being inserted to the list
* newLine: The line the string appeared in
*/
void add2list (ptr *hptr, char* newStr, int newLine) {
  ptr p1, p2;
  ptr t;

  t = (ptr) malloc(sizeof(item)); /*Create a new item in a linked list*/
  
  if(t==NULL) {
    printf("\nCannot allocate memory\n");
    exit(0);
  }
  
  /*initialize the new item*/
  init_item(t);
  t->counter++;
  t->str = malloc(strlen(newStr)*sizeof(char));
  if(t->str==NULL) {
    printf("\nCannot allocate memory\n");
    exit(0);
  }
  t->lines = realloc(t->lines, sizeof(int)*t->counter);
  if(t->lines==NULL) {
    printf("\nCannot allocate memory\n");
    exit(0);
  }
  strcpy(t->str, newStr);
  t->lines[t->counter-1] = newLine;
  
  /*Parse the linked list in order to insert the new item in a lexicographic order*/
  p1 = *hptr;
  while ((p1)&&(strcmp(p1->str, newStr) < 0)) {
    p2 = p1;
    p1 = p1->next;
  }
  
  if (p1 != NULL && strcmp(p1->str, newStr) == 0) { /*Does the new item already exist*/
    int i;
    for (i = 0;i < p1->counter;i++) /*Check if the line is alreay registered*/
      if(p1->lines[i] == newLine) return;
    p1->counter++;
    p1->lines = realloc(p1->lines, sizeof(int)*p1->counter);
    if(p1->lines==NULL) {
      printf("\nCannot allocate memory\n");
      exit(0);
    }
    p1->lines[p1->counter-1] = newLine;
  }
  
  else if (p1 == *hptr) { /*If it doesn't already exist is it the head of the list*/
    *hptr = t;
    t->next = p1;
  }
  
  else { /*Otherwise add it where the while loop stopped*/
    p2->next = t;
    t->next = p1;
  }
}

/*The following function frees allocated memory of a linked list
* *hptr: The head of the linked list*/
void freelist(ptr * hptr) {
  ptr p;
  
  /*Parse the linked list and free each item and its content*/
  while(*hptr) { 
    p = *hptr;
    *hptr = (*hptr)->next;
    free(p->lines);
    free(p->str);
    free(p);
  }
}

/*The following function resets the values of an item in a linked list
* newItem: The item being intialized and reset*/
void init_item(ptr newItem) {
  newItem->lines = malloc(sizeof(int));
  if(newItem->lines==NULL) {
    printf("\nCannot allocate memory\n");
    exit(0);
  }
  newItem->counter = 0;
  newItem->next = NULL;
}

/*The following function parses a linked list and prints out to the stdout which string appears in which lines
* h: The head of the linked list being printed*/
void print_list(ptr h) {
  int i;
  printf("\n");
  while(h) {
    printf("%s\tappears in lines ", h->str);
    for(i = 0;i < h->counter-1;i++) printf("%d,", h->lines[i]);
    printf("%d", h->lines[i]);
    printf("\n");
    h=h->next;
  }
  printf("\n");
}
