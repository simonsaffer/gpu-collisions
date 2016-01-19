/*
 *  obb_detector.cpp
 *  Collision
 *
 *  Created by Exjobb on 10/30/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "obb_detector.h"
#include "bytes_per_object.h"
#include "matrixmath.h"


OBBDetector::OBBDetector(GLuint program, int nbrOfObjects): GPUCollisionDetector(program, nbrOfObjects) {
	// Set up data specific to the OBB detector
	u_nbrOfObjects_loc = glGetUniformLocation(program, "nbrOfObjects");
	u_transform_loc = glGetUniformLocation(program, "u_transform");
	theInData = new GLubyte[nbrOfObjects*nbrOfObjects*BYTES_PER_OBJECT]();
	collisionDetectionResult = new GLubyte[nbrOfObjects*nbrOfObjects*4]();
}

std::vector<std::pair<int,int> > OBBDetector::doCollisionDetection(std::vector<PhysicalObject>& objects,GLuint fb){

	int nbrOfObjects = objects.size();
	
	glUseProgram(program);
	
	// Ta bort efter test!!!!!!!!!!!!
	/*
	for (int i = 0; i<nbrOfObjects*nbrOfObjects*BYTES_PER_OBJECT; i++) {
		theInData[i] = 255;
	}
	*/
	
	GLubyte tmp[4];
	
	// Prepare the in-data	
	for (int i = 0; i<nbrOfObjects; i++) {
		
		esMatrixMultiplyWithVector(tmp, &objects[i].transform, objects[i].bb.origin);
		theInData[i*BYTES_PER_OBJECT   ] = tmp[0];
		theInData[i*BYTES_PER_OBJECT+1 ] = tmp[1];
		theInData[i*BYTES_PER_OBJECT+2 ] = tmp[2];
		theInData[i*BYTES_PER_OBJECT+3 ] = tmp[3];
		
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT   ] = tmp[0];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+1 ] = tmp[1];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+2 ] = tmp[2];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+3 ] = tmp[3];
		
		
		esMatrixMultiplyWithVector(tmp, &objects[i].transform, objects[i].bb.baseVector1);
		theInData[i*BYTES_PER_OBJECT+4 ] = tmp[0];
		theInData[i*BYTES_PER_OBJECT+5 ] = tmp[1];
		theInData[i*BYTES_PER_OBJECT+6 ] = tmp[2];
		theInData[i*BYTES_PER_OBJECT+7 ] = tmp[3];
		
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+4 ] = tmp[0];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+5 ] = tmp[1];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+6 ] = tmp[2];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+7 ] = tmp[3];
		
		esMatrixMultiplyWithVector(tmp, &objects[i].transform, objects[i].bb.baseVector2);
		theInData[i*BYTES_PER_OBJECT+8 ] = tmp[0];
		theInData[i*BYTES_PER_OBJECT+9 ] = tmp[1];
		theInData[i*BYTES_PER_OBJECT+10] = tmp[2];
		theInData[i*BYTES_PER_OBJECT+11] = tmp[3];
		
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+8 ] = tmp[0];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+9 ] = tmp[1];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+10] = tmp[2];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+11] = tmp[3];
		
		esMatrixMultiplyWithVector(tmp, &objects[i].transform, objects[i].bb.baseVector3);
		theInData[i*BYTES_PER_OBJECT+12] = tmp[0];
		theInData[i*BYTES_PER_OBJECT+13] = tmp[1];
		theInData[i*BYTES_PER_OBJECT+14] = tmp[2];
		theInData[i*BYTES_PER_OBJECT+15] = tmp[3];
		
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+12] = tmp[0];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+13] = tmp[1];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+14] = tmp[2];
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+15] = tmp[3];
		
		// Halflengts
		theInData[i*BYTES_PER_OBJECT+16] = objects[i].bb.halfLength1;
		theInData[i*BYTES_PER_OBJECT+17] = objects[i].bb.halfLength2;
		theInData[i*BYTES_PER_OBJECT+18] = objects[i].bb.halfLength3;
		theInData[i*BYTES_PER_OBJECT+19] = objects[i].bb.halfLength3+1;
		
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+16] = objects[i].bb.halfLength1;
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+17] = objects[i].bb.halfLength2;
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+18] = objects[i].bb.halfLength3;
		theInData[i*nbrOfObjects*BYTES_PER_OBJECT+19] = objects[i].bb.halfLength3+1;
		
	}
	
	
	
	printf("\n\nInput: \n");
	
	for (int i = 0; i<nbrOfObjects*nbrOfObjects*BYTES_PER_OBJECT; i+=BYTES_PER_OBJECT) {
		for (int j = 0; j<BYTES_PER_OBJECT; j++) {
			printf("%d ",theInData[i + j]);
		}
		printf("\n");
	}
	
	/*
	for (int i = 0; i<nbrOfObjects; i++) {
		printf("\n");
		for (int j = 0; j<nbrOfObjects*BYTES_PER_OBJECT; j+=BYTES_PER_OBJECT) {
			for (int k = 0; k<BYTES_PER_OBJECT; k++) {
			printf(" %d",theInData[i*nbrOfObjects*BYTES_PER_OBJECT+j*BYTES_PER_OBJECT+k]);
			}
			printf(" |");
		}
		
	}*/
	
	// Felet verkar vara i shadern
	
	//glUniformMatrix4fv(u_transform_loc, 1, GL_FALSE, t) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	
	// Behovs flera texturer eller kan man ta hand om det genom att satta viewPort?
	
	// Lagg in datan pa texturen in_data som textur 0
	glActiveTexture(GL_TEXTURE0);			
	glBindTexture(GL_TEXTURE_2D, in_data);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nbrOfObjects*TEXELS_PER_OBJECT, nbrOfObjects, 0, GL_RGBA, GL_UNSIGNED_BYTE, theInData);
	glUniform1i(s_srcTex_loc, 0);
	glUniform1f(u_nbrOfObjects_loc, static_cast<float> (nbrOfObjects));
	
	
	doCalculations(nbrOfObjects,fb);
	
	texHandler.getArray(result, collisionDetectionResult);
	
	printf("\n\nOutput:\n");
	
	for (int i = 0; i<nbrOfObjects; i++) {
		printf("\n");
		for (int j = 0; j<nbrOfObjects; j++) {
			printf("%d %d %d %d | ", collisionDetectionResult[nbrOfObjects*4*i+j*4], collisionDetectionResult[nbrOfObjects*4*i+j*4+1], collisionDetectionResult[nbrOfObjects*4*i+j*4+2], collisionDetectionResult[nbrOfObjects*4*i+j*4+3]);
		}
	}
	
	return getCollidingObjects(nbrOfObjects, collisionDetectionResult);
	
}