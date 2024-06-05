/*The following program includes functions that do operations on matrices*/

#include "mymat.h"

/* Adds two matrices and stores the result in another matrix.
 * mat1: Pointer to the first matrix
 * mat2: Pointer to the second matrix
 * mat3: Pointer to the matrix to store the result
 * returns: 0 if operation is successful
 */
int add_mat(mat* mat1, mat* mat2, mat* mat3) {
  int i;
  int j;
  
  for(i = 0;i<MAT_SIZE;i++) {
    for(j = 0;j<MAT_SIZE;j++) {
      mat3->data[i][j] = mat1->data[i][j]+mat2->data[i][j];
    }
  }
  return 0;
}

/* Subtracts one matrix from another and stores the result in another matrix.
 * mat1: Pointer to the first matrix
 * mat2: Pointer to the second matrix
 * mat3: Pointer to the matrix to store the result
 * returns: 0 if operation is successful
 */
int sub_mat(mat* mat1, mat* mat2, mat* mat3) {
  int i;
  int j;
  
  for(i = 0;i<MAT_SIZE;i++) {
    for(j = 0;j<MAT_SIZE;j++) {
      mat3->data[i][j] = mat1->data[i][j]-mat2->data[i][j];
    }
  }
  return 0;
}

/* Multiplies two matrices and stores the result in another matrix.
 * mat1: Pointer to the first matrix
 * mat2: Pointer to the second matrix
 * mat3: Pointer to the matrix to store the result
 * returns: 0 if operation is successful
 */
int mul_mat(mat* mat1, mat* mat2, mat* mat3) {
  int i;
  int j;
  int k;
  float sum;
  
  for(i = 0;i<MAT_SIZE;i++) {
    for(j = 0;j<MAT_SIZE;j++) {
      for(k = 0;k<MAT_SIZE;k++) {
        sum+=mat1->data[i][k]*mat2->data[k][j];
      }
      mat3->data[i][j] = sum;
    }
  }
  return 0;
}

/* Multiplies a matrix by a scalar and stores the result in another matrix.
 * mat1: Pointer to the matrix
 * scale: Scalar value to multiply with the matrix
 * mat2: Pointer to the matrix to store the result
 * returns: 0 if operation is successful
 */
int mul_scalar_mat(mat* mat1, float scale, mat* mat2) {
  int i;
  int j;
  
  for(i = 0;i<MAT_SIZE;i++) {
    for(j = 0;j<MAT_SIZE;j++) {
      mat2->data[i][j] = mat1->data[i][j]*scale;
    }
  }
  return 0;
}

/* Transposes a matrix and stores the result in another matrix.
 * mat1: Pointer to the matrix to be transposed
 * mat2: Pointer to the matrix to store the transposed result
 * returns: 0 if operation is successful
 */
int trans_mat(mat* mat1, mat* mat2){
  int i;
  int j;
  
  for(i = 0;i<MAT_SIZE;i++) {
    for(j = 0;j<MAT_SIZE;j++) {
      mat2->data[i][j] = mat1->data[j][i];
    }
  }
  return 0;
}
