/*
* The following program calculates the cosine of a given degree using the Taylor series to an accuracy of 1.0e-6.
* Then it compares the result to the cosine from math.h and prints both.
* The program contains 3 function: main, my_cos and factorial.
* The program will first take the degree the user wants to calculate the cosine of, send it to my_cos function and then print it.
* After that, the program will use the cos function of math.h to calculate the cosine of the degree and print that also.
* We are assuming the input is valid.
*/

#include <stdio.h>
#include <math.h>

/* The following fuction calculates the factorial of a given number (num)*/
double factorial (int num) {
  double sum = 1;
  if(num==0) return 0; /*If the given number is 0 then its factorial is also 0*/
  while (num!=0) {
    sum*=(double)num;
    num--;
  }
  
  return sum;
}

/*The following function calculates the cosine of a degree using the Taylor series*/
double my_cos(double deg) {
  
  int n = 1;
  double result = 1.0;
  double dist = 1.0;
  
  while(1.0e-6<=fabs(dist)) { /*Run until an accuracy of 1.0e-6*/
    dist = pow(-1, n)*pow(deg, 2*n)/factorial(2*n); /*The Taylor series*/
    result+=dist;
    n++;
  }
  
  return result;
}

/*Takes an input from the user and calculates the cosine of it using my_cos and math.h's cos.
We are assuming valid input*/
int main() {
  double input;
  
  printf("Enter the degree you want to cosine: ");
  scanf("%lf", &input);
  
  /*Compares the results of the two cosine functions*/
  printf("\nThe cosine of %f using my cosine funcstion is: %f\n", input, my_cos(input));
  printf("The cosine of %f using math.h cosine funcstion is: %f\n", input, cos(input));
  
  return 0;
}
