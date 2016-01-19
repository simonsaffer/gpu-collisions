
#include "esUtil.h"
#include "matrixmath.h"

#ifdef _WIN32
	#include <GLES2/gl2.h>
#else
	#include <OpenGLES/ES2/gl.h>
#endif


#include <cstdio>
#include <cstdlib>
#include <cstring>



/*
*	4x4 matrix inverse.
*	Based on:http://gpwiki.org/index.php/MathGem:Fast_Matrix_Inversion
*	only works for camera matrixes!
*/
void esMatrixInverse(ESMatrix* result,ESMatrix* mat){
	
	/*
	*	M4x4 =	|R t|
	*			|0 1|
	*
	*	inv =	|R' -R'*t| 
	*			|0   1  |
	*/


	ESMatrix R,inv;
	//make inv to I (makes sure that it has valid numbers)
	esMatrixLoadIdentity(&inv);

	//zero the 4th column and row, R is only the first 3x3 matrix
	for(int j=0;j<4;j++){
		R.m[3][j]=0.0f;
		R.m[j][3]=0.0f;
	}
	
	//copy the values of te 3x3 matrix
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			R.m[i][j]=mat->m[i][j];			
		}
	}
	//transpose,  R is now R'
	esMatrixTranspose(&R,&R);
	//sets inv =	|R' 0|
	//				|0  1|
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			inv.m[i][j]=R.m[i][j];
		}
	}

	float x,y,z;
	float t[3];
	t[0]=mat->m[3][0];
	t[1]=mat->m[3][1];
	t[2]=mat->m[3][2];
	x=(R.m[0][0]*t[0])+(R.m[1][0]*t[1])+(R.m[2][0]*t[2]); //R'x dot t
	y=(R.m[0][1]*t[0])+(R.m[1][1]*t[1])+(R.m[2][1]*t[2]); //R'y dot t
	z=(R.m[0][2]*t[0])+(R.m[1][2]*t[1])+(R.m[2][2]*t[2]); //R'z dot t
	inv.m[3][0]=-x;
	inv.m[3][1]=-y;
	inv.m[3][2]=-z;

	memcpy(&result->m[0][0],&inv.m[0][0],sizeof(GLfloat)*4*4);
	
}


void esMatrixTranspose(ESMatrix* result,ESMatrix* mat){
	ESMatrix tmp;
	for(int j=0;j<4;j++){
		for(int i=0;i<4;i++){
			tmp.m[j][i]=mat->m[i][j];
		}
	}
	memcpy(&result->m[0][0],&tmp.m[0][0],sizeof(GLfloat)*4*4);
}
/*
*	for debugging
*/
void printMatrix(ESMatrix* matrix){
	
	for(int j=0;j<4;j++){
		for(int i=0;i<4;i++){
			printf("%f ",matrix->m[i][j]);
		}
		printf("\n");
	}
}

void esMatrixMultiplyWithVector(GLfloat* result,ESMatrix* matrix, GLfloat* vec){
	//assumes that matrix is 4x4 and vector is 4x1
	
	result[0] = matrix->m[0][0]*vec[0] + matrix->m[0][1]*vec[1] + matrix->m[0][2]*vec[2] + matrix->m[0][3]*vec[3];
	result[1] = matrix->m[1][0]*vec[0] + matrix->m[1][1]*vec[1] + matrix->m[1][2]*vec[2] + matrix->m[1][3]*vec[3];
	result[2] = matrix->m[2][0]*vec[0] + matrix->m[2][1]*vec[1] + matrix->m[2][2]*vec[2] + matrix->m[2][3]*vec[3];
	result[3] = matrix->m[3][0]*vec[0] + matrix->m[3][1]*vec[1] + matrix->m[3][2]*vec[2] + matrix->m[3][3]*vec[3];
}



void esMatrixMultiplyWithVector(GLubyte* result, ESMatrix* matrix, GLubyte* vec){
	
	result[0] = matrix->m[0][0]*vec[0] + matrix->m[0][1]*vec[1] + matrix->m[0][2]*vec[2] + matrix->m[0][3]*vec[3];
	result[1] = matrix->m[1][0]*vec[0] + matrix->m[1][1]*vec[1] + matrix->m[1][2]*vec[2] + matrix->m[1][3]*vec[3];
	result[2] = matrix->m[2][0]*vec[0] + matrix->m[2][1]*vec[1] + matrix->m[2][2]*vec[2] + matrix->m[2][3]*vec[3];
	result[3] = matrix->m[3][0]*vec[0] + matrix->m[3][1]*vec[1] + matrix->m[3][2]*vec[2] + matrix->m[3][3]*vec[3];

	
}


