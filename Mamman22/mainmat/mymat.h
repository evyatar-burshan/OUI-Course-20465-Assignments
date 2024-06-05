/*Header file for mainmat.c*/

#define MAT_SIZE 4 /*Defines the size of the matrices used in the pocket caluclator*/
typedef struct {float data[MAT_SIZE][MAT_SIZE];} mat;

/* Adds two matrices and stores the result in another matrix.
 * mat1: Pointer to the first matrix
 * mat2: Pointer to the second matrix
 * mat3: Pointer to the matrix to store the result
 * returns: 0 if operation is successful
 */
int add_mat(mat* mat1, mat* mat2, mat* mat3);

/* Subtracts one matrix from another and stores the result in another matrix.
 * mat1: Pointer to the first matrix
 * mat2: Pointer to the second matrix
 * mat3: Pointer to the matrix to store the result
 * returns: 0 if operation is successful
 */
int sub_mat(mat* mat1, mat* mat2, mat* mat3);

/* Multiplies two matrices and stores the result in another matrix.
 * mat1: Pointer to the first matrix
 * mat2: Pointer to the second matrix
 * mat3: Pointer to the matrix to store the result
 * returns: 0 if operation is successful
 */
int mul_mat(mat* mat1, mat* mat2, mat* mat3);

/* Multiplies a matrix by a scalar and stores the result in another matrix.
 * mat1: Pointer to the matrix
 * scale: Scalar value to multiply with the matrix
 * mat2: Pointer to the matrix to store the result
 * returns: 0 if operation is successful
 */
int mul_scalar_mat(mat* mat1, float scale, mat* mat2);

/* Transposes a matrix and stores the result in another matrix.
 * mat1: Pointer to the matrix to be transposed
 * mat2: Pointer to the matrix to store the transposed result
 * returns: 0 if operation is successful
 */
int trans_mat(mat* mat1, mat* mat2);
