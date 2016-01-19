#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

/*
*	complmeneting fuctions for ESMatrix
*	writen as in esUtil
*/

#include "esUtil.h"

void esMatrixInverse(ESMatrix* result,ESMatrix* mat);

void esMatrixTranspose(ESMatrix* result,ESMatrix* mat);
	
void printMatrix(ESMatrix* matrix);

void esMatrixMultiplyWithVector(GLfloat* result, ESMatrix* matrix, GLfloat* vector);

void esMatrixMultiplyWithVector(GLubyte* result, ESMatrix* matrix, GLubyte* vector);


#endif