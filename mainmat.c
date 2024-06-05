/* The following program is a command-line pocket calculator designed to perform matrix operations. It allows users to input commands to manipulate up to six matrices named  * MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, and MAT_F. Supported operations include reading matrices, printing matrices, adding, subtracting, and multiplying matrices, multiplying  * a matrix by a scalar, and finding the transpose of a matrix. The program ensures proper validation of user input, including checking for missing arguments, illegal commas, * and extraneous text. It will print out the input when given.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mymat.h"

#define BUFFER 2048 /*Buffer for input so it won't be too long*/

void init_mat(mat* mat1);
int read_mat(mat* mat1, float mat2[MAT_SIZE][MAT_SIZE]);
int print_mat(mat* mat1);
int is_valid_input(char* input, mat* matA, mat* matB, mat* matC, mat* matD, mat* matE, mat* matF);
mat* is_valid_mat_name (char* matName, mat* matA, mat* matB, mat* matC, mat* matD, mat* matE, mat* matF);
int is_extra_text(char* arg);
int is_missing_arg(char* arg);
int is_illegal_comma(char* arg);
int is_missing_comma(char* arg);

/*The following program intializes the matrices and begins the program*/
int main() {
  static mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F; /* Basix matrices*/
  char input[BUFFER];
  
  /*Initializing all matrices to 0*/
  init_mat(&MAT_A);
  init_mat(&MAT_B);
  init_mat(&MAT_C);
  init_mat(&MAT_D);
  init_mat(&MAT_E);
  init_mat(&MAT_F);
  
  printf("This is a pocket calculator that works on 6 matrices: MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F.\nPlease enter one of the following commands. Commands are to be spelled in small letters, matrices names in capital letters  and arguments are seperated by commass. Ex: trans_mat MAT_A, MAT_B.");
  printf("\nCommands:\n\t1. read_mat MAT, up to 16 arguments(numbers)\n\t2. print_mat MAT\n\t3. add_mat MAT1, MAT2, MAT DESTINATION\n\t4. sub_mat MAT1, MAT2, MAT DESTINATION\n\t5. mul_mat MAT1, MAT2, MAT DESTINATION\n\t6. mul_scalar MAT1, scale(number), MAT DESTINATION\n\t7. trans_mat MAT, MAT DESTINATION\n\t8. stop\n\n\n");
  printf("> The program is ready to take input:\n");
  
  while( fgets(input, sizeof(input), stdin) != 0) { /*Repeat until end of input/program is stopped properly*/
    input[strcspn(input, "\n")] = '\0'; /*Remove newline character from input*/
    printf("> %s:\n", input);
    is_valid_input(input, &MAT_A, &MAT_B, &MAT_C, &MAT_D, &MAT_E, &MAT_F);
    printf("\n> The program is ready to take input:\n");
  }
  printf("\nProgram ended wrongly\n");
  return 0;
}

/*Sets all of a matrices values to 0
 * mat1: The address of the mat intialized*/
void init_mat(mat* mat1) {
  int i;
  int j;
  
  for(i = 0;i<MAT_SIZE;i++) {
    for(j = 0;j<MAT_SIZE;j++) {
      mat1->data[i][j] = 0;
    }
  }
}

/* Reads a matrix of float values and enters them into a matrix
 * mat1: The address of the mat read
 * mat2: The mat of values
 * returns: 0 if successful*/  
int read_mat(mat* mat1, float mat2[MAT_SIZE][MAT_SIZE]) {
  int i;
  int j;
  
  for(i = 0;i<MAT_SIZE;i++) {
    for(j = 0;j<MAT_SIZE;j++) {
      mat1->data[i][j] = mat2[i][j];
    }
  }
  return 0;
}

/* Prints a matrix from a given address
 * mat1: The address of the mat to print
 * returns: 0 if successful*/
int print_mat(mat* mat1) {
  int i;
  int j;
  
  for(i = 0;i<MAT_SIZE;i++) {
    for(j = 0;j<MAT_SIZE;j++) {
      printf("%7.2f", mat1->data[i][j]);
    }
    printf("\n");
  }
  return 0;
}

/*Checks if the input is valid and executes the command specified in the input
 * input: The string of the input
 * matA: The address of MAT_A
 * matB: The address of MAT_B
 * matC: The address of MAT_C
 * matD: The address of MAT_D
 * matE: The address of MAT_E
 * matF: The address of MAT_F
 * returns: 0 if successful*/
int is_valid_input(char* input, mat* matA, mat* matB, mat* matC, mat* matD, mat* matE, mat* matF) {
  char* curArg = strtok(input, " ");
  char function[BUFFER];
  char* delim = " ,";
  mat* mat1;
  mat* mat2;
  mat* mat3;
  
  if(curArg==NULL) return 1;
  
  strncpy(function, curArg, sizeof(function)); /*Seperate the function from the rest of the input*/
  
  /*Commands with 0 matrices*/
  if (strcmp(function, "stop") == 0) {
    curArg = strtok(NULL, " ");
    if(is_extra_text(curArg)==1) return 1;
    exit(0); /*Executes the command successfully*/
  }
  
  /*Commands with 1 matrix*/
  else {
    curArg = strtok(NULL, " "); /*Get the next argument*/
    /*Validity Checks for the current argument*/
    if(is_missing_arg(curArg)==1) return 1;
    if(is_illegal_comma(curArg)) {
      printf("\nMultiple consecutive commas\n");
      return 1;
    }
    if(is_missing_comma(curArg)==1) return 1;
    curArg[strcspn(curArg, delim)] = '\0';
    mat1 = is_valid_mat_name(curArg, matA, matB, matC, matD, matE, matF);
    if(mat1==NULL) return 1; /*Validity Check for the matrix*/

    if (strcmp(function, "read_mat") == 0) {
      float nums[MAT_SIZE][MAT_SIZE] = {0};
      float curNum;
      int i;
      int j;
      int k;
    
      curArg = strtok(NULL, delim);
      /*Validity Checks for the current argument*/
      if(is_missing_arg(curArg)==1) return 1;
      if(is_illegal_comma(curArg)) {
        printf("\nMultiple consecutive commas\n");
        return 1;
      }
      if(is_missing_comma(curArg)==1) return 1;
      
      /*Check validity of input by comparing input to ASCII values*/
      for (k = 0; k<strlen(curArg); k++) {
        if(isspace(curArg[k])) continue;
        if(!(curArg[k] == 45 || curArg[k] == 46 || curArg[k] == 48 || curArg[k] == 49 || curArg[k] == 50 || curArg[k] == 51 || curArg[k] == 52 || curArg[k] == 53 ||
           curArg[k] == 54 || curArg[k] == 55 || curArg[k] == 56 || curArg[k] == 57)) {
          printf("\nArgument is not a real number\n");
          return 1;
        }
      }
      for (i = 0;i<MAT_SIZE && curArg != NULL;i++) {
        for (j = 0;j<MAT_SIZE && curArg != NULL;j++) {
          /*Check validity of input by comparing input to ASCII values*/
          for (k = 0; k<strlen(curArg); k++) {
            if(isspace(curArg[k])) continue;
            if(!(curArg[k] == 45 || curArg[k] == 46 || curArg[k] == 48 || curArg[k] == 49 || curArg[k] == 50 || curArg[k] == 51 || curArg[k] == 52 || curArg[k] == 53 ||
               curArg[k] == 54 || curArg[k] == 55 || curArg[k] == 56 || curArg[k] == 57)) {
              printf("\nArgument is not a real number\n");
              return 1;
            }
          }
          curNum = atof(curArg);
          nums[i][j] = curNum;
          curArg = strtok(NULL, delim);
          
        }
      }
      read_mat(mat1, nums); /*Executes the command successfully*/
      return 0;
    } 
    else if (strcmp(function, "print_mat") == 0) {
      curArg = strtok(NULL, " ");
      if(is_extra_text(curArg)==1) return 1;
      print_mat(mat1); /*Executes the command successfully*/
    }
    
    /*Commands with 2 matrices*/
    else {
  
      if (strcmp(function, "mul_scalar") == 0) {
        float scale;
        int k;
        
        curArg = strtok(NULL, delim);
        /*Validity Checks for the current argument*/
        if(is_missing_arg(curArg)==1) return 1;
        if(is_illegal_comma(curArg)) {
          printf("\nMultiple consecutive commas\n");
          return 1;
        }
        if(is_missing_comma(curArg)==1) return 1;
        
        /*Check validity of input by comparing input to ASCII values*/
        for (k = 0; k<strlen(curArg); k++) {
          if(isspace(curArg[k])) continue;
          if(!(curArg[k] == 45 || curArg[k] == 46 || curArg[k] == 48 || curArg[k] == 49 || curArg[k] == 50 || curArg[k] == 51 || curArg[k] == 52 || curArg[k] == 53 ||
             curArg[k] == 54 || curArg[k] == 55 || curArg[k] == 56 || curArg[k] == 57)) {
            printf("\nArgument is not a scalar\n");
            return 1;
          }
        }
        scale = atof(curArg);
        curArg = strtok(NULL, delim);
        /*Validity Checks for the current argument*/
        if(is_missing_arg(curArg)==1) return 1;
        if(is_illegal_comma(curArg)) {
          printf("\nMultiple consecutive commas\n");
          return 1;
        }
        if(is_missing_comma(curArg)==1) return 1;
        mat2 = is_valid_mat_name(curArg, matA, matB, matC, matD, matE, matF);
        if(mat2==NULL) return 1; /*Validity Check for the matrix*/
        
        curArg = strtok(NULL, " ");
        if(is_extra_text(curArg)==1) return 1;
        mul_scalar_mat(mat1, scale, mat2); /*Executes the command successfully*/
      }
      
      /*Commands with 3 matrices*/
      else {
        curArg = strtok(NULL, delim);
        /*Validity Checks for the current argument*/
        if(is_missing_arg(curArg)==1) return 1;
        if(is_illegal_comma(curArg)) {
          printf("\nMultiple consecutive commas\n");
          return 1;
        }
        if(is_missing_comma(curArg)==1) return 1;
        mat2 = is_valid_mat_name(curArg, matA, matB, matC, matD, matE, matF);
        if(mat2==NULL) return 1; /*Validity Check for the matrix*/
        
        if (strcmp(function, "trans_mat") == 0) {
          curArg = strtok(NULL, " ");
	  if(is_extra_text(curArg)==1) return 1;
          trans_mat(mat1, mat2); /*Executes the command successfully*/
        }
        else {
  
          curArg = strtok(NULL, delim);
          if(is_missing_arg(curArg)==1) return 1;
          if(is_illegal_comma(curArg)) {
            printf("\nMultiple consecutive commas\n");
            return 1;
          }
          if(is_missing_comma(curArg)==1) return 1;
          mat3 = is_valid_mat_name(curArg, matA, matB, matC, matD, matE, matF);
          if(mat3==NULL) return 1; /*Validity Check for the matrix*/
          
          curArg = strtok(NULL, " ");
          if(is_extra_text(curArg)==1) return 1;
          
          if (strcmp(function, "add_mat") == 0) {
            add_mat(mat1, mat2, mat3); /*Executes the command successfully*/
          }
          else if (strcmp(function, "sub_mat") == 0) {
            sub_mat(mat1, mat2, mat3); /*Executes the command successfully*/
          }
          else if (strcmp(function, "mul_mat") == 0) {
            mul_mat(mat1, mat2, mat3); /*Executes the command successfully*/
          }
          else {
            if(strchr(function, 44)) {
              printf("\nIllegal Comma\n");
              return 1;
            }
            printf("\nUndefined command name\n");
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

/*Checks if the given string is one of the matrices in the program
 * matName: The string being checked
 * matA: The address of MAT_A
 * matB: The address of MAT_B
 * matC: The address of MAT_C
 * matD: The address of MAT_D
 * matE: The address of MAT_E
 * matF: The address of MAT_F
 * returns: NULL if matName is not one of the matrices in the program, otherwise it returns the address of the mmatrix*/
mat* is_valid_mat_name (char* matName, mat* matA, mat* matB, mat* matC, mat* matD, mat* matE, mat* matF) {
  if (strcmp(matName, "MAT_A") == 0) return matA;
  else if (strcmp(matName, "MAT_B") == 0) return matB;
  else if (strcmp(matName, "MAT_C") == 0) return matC;
  else if (strcmp(matName, "MAT_D") == 0) return matD;
  else if (strcmp(matName, "MAT_E") == 0) return matE;
  else if (strcmp(matName, "MAT_F") == 0) return matF;
  else {
  printf("\nUndefined matrix name\n");
  return NULL;
  }
}

/*Checks for extra text after curArg in is_valid_input()
 * arg: The string that is checked to be NULL
 * returns: 1 if it is not NULL, 0 if otherwise*/
int is_extra_text(char* arg) {
  if(arg!=NULL && !isspace(*arg)) {
    printf("\nExtraneous text after end of command\n");
    return 1;
  }
  return 0;
}

/*Checks for missing text in curArg in is_valid_input()
 * arg: The string that is checked to be NULL
 * returns: 1 if it is NULL, 0 if otherwise*/
int is_missing_arg(char* arg) {
  if(arg==NULL) {
    printf("\nMissing Argument\n");
    return 1;
  }
  return 0;
}

/*Checks for illegal commas in curArg in is_valid_input()
 * arg: The string that is checked to have commas
 * returns: 1 if it is has commas, 0 if otherwise*/
int is_illegal_comma(char* arg) {
  int i, count;
  for (i=0, count=0; arg[i]; i++)
    count += (arg[i] == ',');
  if(count>1)
    return 1;
  return  0;
}

/*Checks for missing commas in curArg in is_valid_input()
 * arg: The string that is checked to not have commas
 * returns: 1 if it is misses commas, 0 if otherwise*/
int is_missing_comma(char* arg) {
  if(strchr(arg, 32)) {
    printf("\nMissing comma\n");
    return 1;
  }
  return  0;
}
