/*
 *  sphere_detector.cpp
 *  Collision
 *
 *  Created by Exjobb on 10/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "sphere_detector.h"
#include "esUtil.h"


SphereDetector::SphereDetector(GLuint program, int nbrOfObjects): GPUCollisionDetector(program,nbrOfObjects) {
	
	// The 4 in the size is for x,y,z and radius for each sphere
	theInData = new GLubyte[nbrOfObjects*nbrOfObjects*4]();
	
	collisionDetectionResult = new GLubyte[nbrOfObjects*nbrOfObjects*4];
}



std::vector<std::pair<int,int> > SphereDetector::doCollisionDetection(std::vector<PhysicalObject>& objects,GLuint fb){
	
	glUseProgram(program);
	
	
	int nbrOfObjects = objects.size();
	
	// Set up the table with data to be used in collision detection
	for (int i = 0; i<nbrOfObjects; i++) {
		theInData[i*4] = (objects[i].boundingSphere.x);
		theInData[i*4+1] = (objects[i].boundingSphere.y);
		theInData[i*4+2] = (objects[i].boundingSphere.z);
		theInData[i*4+3] = (objects[i].boundingSphere.r);
	}
	
	for (int j = 0; j<nbrOfObjects; j++) {
		theInData[j*nbrOfObjects*4] = (objects[j].boundingSphere.x);
		theInData[j*nbrOfObjects*4+1] = (objects[j].boundingSphere.y);
		theInData[j*nbrOfObjects*4+2] = (objects[j].boundingSphere.z);
		theInData[j*nbrOfObjects*4+3] = (objects[j].boundingSphere.r);
	}
	
	
	printf("\nInput:");
	for (int i = 0; i<nbrOfObjects; i++) {
		printf("\n");
		for (int j = 0; j<nbrOfObjects; j++) {
			printf("%d %d %d %d | ", theInData[nbrOfObjects*4*i+j*4], theInData[nbrOfObjects*4*i+j*4+1], theInData[nbrOfObjects*4*i+j*4+2], theInData[nbrOfObjects*4*i+j*4+3]);
		}
	}
	
	//GLubyte *inDataP = (GLubyte*) theInData;
	
	
	// Lagg in datan pa texturen in_data som textur 0
	glActiveTexture(GL_TEXTURE0);			// Ar dessa raderna
	glBindTexture(GL_TEXTURE_2D, in_data);	// onodigt extra-arbete?????????
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nbrOfObjects, nbrOfObjects, 0, GL_RGBA, GL_UNSIGNED_BYTE, theInData);
	glUniform1i(s_srcTex_loc, 0);
	
	
	doCalculations(nbrOfObjects, fb);
	
	texHandler.getArray(result, collisionDetectionResult);
	
	
	printf("\n\nOutput:");
	for (int i = 0; i<nbrOfObjects; i++) {
		printf("\n");
		for (int j = 0; j<nbrOfObjects; j++) {
			printf("%d %d %d %d | ", collisionDetectionResult[nbrOfObjects*4*i+j*4], collisionDetectionResult[nbrOfObjects*4*i+j*4+1], collisionDetectionResult[nbrOfObjects*4*i+j*4+2], collisionDetectionResult[nbrOfObjects*4*i+j*4+3]);
		}
	}
	
	
	return getCollidingObjects(nbrOfObjects, collisionDetectionResult);
	
}
