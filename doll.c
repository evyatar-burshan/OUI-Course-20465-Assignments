/*
* The following program prints out a table of dollar values converted to NIS.
* It will do that by first asking the user what is dollar to NIS rate. Then,
* it will take input until EOF of dollar values to convert and handle each case separately.
* Eventually the program prints out the sum of all values.
* We are assuming that the user will not input wrong values (such as negatives).
*/

#include <stdio.h>



/*The following function asks for the dollar to NIS rate. Then, takes input until EOF of dollar values to convert and handles each case separately. Eventually the function prints out the sum of all values.
We are assuming that the user will not input wrong values (such as negatives).*/
int main()
{
  float dolToNis; /* Dollar to NIS rate*/
  float curVal; /* Current input recieved from the user*/
  float sum = 0.0; /* Sum of all dollar values*/
  
  printf("Please enter the dollar to NIS rate: ");
  scanf("%f", &dolToNis); /* Request the dollar to NIS rate*/
  
  /* Print out the table headers*/
  printf("\n\n $");
  printf("%12s\n", "IS");
  
  /* Convert dollar to NIS values until EOF*/
  while (scanf("%f", &curVal) != EOF) {
    sum+=curVal;
    printf("%6.2f", curVal);
    printf("%11.2f\n", curVal*dolToNis);
    
  }
  
  /*Print out the sum of all values*/
  printf("%6.2f", sum);
  printf("%11.2f\n", sum*dolToNis);
  
  
  return 0;
}
