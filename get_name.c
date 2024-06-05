/*
* The following program will ask the user to enter 30 different names without white spaces using only the English alphabet which are no longer than 20 charcters.
* Input from the standard input (either file or console). We are assuming the user uses only the English alphabet and names no longer than 20 characters.
* Then, the program will choose 10 names randomly and print them out to the standard output (either file or console).
* The program will execute that by calling the void read_names() function, which will request input from the user and check the validity of it.
* Afterwards, the program will print the list of names using the function void print_names().
* Finally, the program will print out 10 names randomly using get_name() and free up all allocated memory.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define ARR_SIZE 30 /* Number of names the program will need for input*/
#define NAME_SIZE 21 /*Length of the names*/
#define NUM_RAND_NAMES 10 /*Number of names the program will randomize and output*/

/*Declerations of functions that will be used*/
void read_names();
void print_names();
char * get_name();
int strcasecmp (char * s1, char * s2);

/*Declartion of global variables*/
char* names[ARR_SIZE];

/*The following function prints out the request for the user,
* Prints out the list he entered and runs get_name()
* the number of times specified in NUM_RAND_NAMES.
* It will print out the names after each call to get_name()
* Finallt, it will free up allocated memory */
int main() {
  int i;
  
  srand(time(0)); /*Seeding  random  so we will get a random outcome each time*/
  
  printf("Please enter 30 different names without white spaces, using ONLY the English alphabet and no longer than 20 characters:\n");
  read_names();
  printf("\nThe list of names you entered is:\n");
  print_names();
  printf("\nHere are %d random names:\n", NUM_RAND_NAMES);
  
  /*Running the get_name() function NUM_RAND_NAMES times and printing the names out*/
  for (i=0;i<NUM_RAND_NAMES;i++)
    printf("%d. %s\n", i+1, get_name());
  
  /*Freeing up allocated memory*/
  for (i=0;i<ARR_SIZE;i++)
    free(names[i]);
  
  return 0;
}

/*The following function randomizes an index and
* returns the string in global array names corresponding to that index. */
char * get_name(){
  int idxName = rand() % ARR_SIZE;   /*Randomize index in range*/
  char * string = malloc(NAME_SIZE * sizeof(char));
  if (string == NULL) { /*Check if malloc failed*/
    printf("ERROR: malloc failed allocating memory");
    exit(0);
  }
  string = strcpy(string, names[idxName]);
  return string;
}

/*The following function will read ARR_SIZE names from the user and check their validity by these standards:
* The name doesn't already exist in the global names array (ignores case) and there are no white spaces
* (If the program meets white space it will split the name where the white space is. If the input
* is valid, the program will insert it at the next available space in the global array names.
* If the input is not valid it will print out a detailed error message and stop theee program. */
void read_names() {
  int i = 0;
  int j;
  char newName[NAME_SIZE];
  
  while (i<ARR_SIZE && newName != NULL) { /*Runs for ARR_SIZE times and as long as the new input isn't NULL*/
    j = 0;
    scanf("%s", newName); /*Get new name*/
    newName[strcspn(newName, "\n")] = '\0'; /*If the name has a new line character in it, replace it.*/
    
    for (j = 0; j < i; j++) { /*Checks for dupicate inputs*/
      if (strcasecmp(names[j], newName)==0) { /*If there is a duplicate end thee program*/
      	printf("ERROR: You entered an identical name to a name you already entered (%s, %s)\n", names[j], newName);
  	exit(0);
      }
    }
    
    names[i] = malloc(NAME_SIZE * sizeof(char));
    if (names[i]==NULL) { /*Check if malloc failed*/
      printf("ERROR: malloc failed allocating memory");
      exit(0);
    }
    strcpy(names[i], newName);/* Add the new VALID name to the global array names*/
    i++;
  }
}

/*The following function will print out the entire global names array*/
void print_names() {
  int i;
  for(i=0;i<ARR_SIZE-1;i++)
    printf("%s, ", names[i]);
  printf("%s", names[i]);
  printf("\n");
}

/*The following function will check if a string is identical to another string.
* It recieves 2 strings (or pointers to them) and returns 0 if they are identical and 1 if they aren't*/
int strcasecmp (char * s1, char * s2) {
  int i;
  if(strlen(s1)!=strlen(s2)) return 1; /*Check if the length of both strings is the same*/

  for(i=0;i<strlen(s1);i++) /*Check if each character is the same using tolower*/
    if(tolower(s1[i])!=tolower(s2[i]))
      return 1;
  return 0;
}
