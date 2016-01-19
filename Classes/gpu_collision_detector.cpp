/*
 *  gpu_collision_detector.cpp
 *  Collision
 *
 *  Created by Exjobb on 10/8/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "gpu_collision_detector.h"
#include "shader_utils.h"
#include "bytes_per_object.h"
#include <utility>


GLfloat GPUCollisionDetector::writeToTextureQuad[20];
GLushort GPUCollisionDetector::writeToTextureIndices[6]; 

GPUCollisionDetector::GPUCollisionDetector(GLuint program, int nbrOfObjects): texHandler(2), program(program) {
	
	
	printf("\nDetection program %d\n",program);
	
	a_position_loc = glGetAttribLocation(program, "a_position");
	a_texCoord_loc = glGetAttribLocation(program, "a_texCoord");
	
	printf("\na_position_loc %d a_texCoord %d\n",a_position_loc,a_texCoord_loc);
	
	s_srcTex_loc = glGetUniformLocation(program, "s_srcTex");
	
	printf("\ns_srcTex_loc %d\n",s_srcTex_loc);
	
	
	
	in_data = texHandler.createArray(nbrOfObjects*TEXELS_PER_OBJECT, nbrOfObjects, (void*) 0);
	
	result = texHandler.createArray(nbrOfObjects, nbrOfObjects, (void*) 0);
	
	printf("\nin_data %d result %d",in_data,result);
	
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, result, 0);
	
	//assert(glGetError()==GL_NO_ERROR);
	//assert(glCheckFramebufferStatus(GL_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE);
	
	
	
	writeToTextureQuad[0] = -1.0f; writeToTextureQuad[1] =  1.0f; writeToTextureQuad[2] =  0.0f;
	writeToTextureQuad[3] =  0.0f; writeToTextureQuad[4] =  1.0f;
	
	writeToTextureQuad[5] = -1.0f; writeToTextureQuad[6] = -1.0f; writeToTextureQuad[7] =  0.0f;
	writeToTextureQuad[8] =  0.0f; writeToTextureQuad[9] =  0.0f;
	
	writeToTextureQuad[10] =  1.0f; writeToTextureQuad[11] =  -1.0f; writeToTextureQuad[12] =  0.0f;
	writeToTextureQuad[13] =  1.0f; writeToTextureQuad[14] =  0.0f;
	
	writeToTextureQuad[15] =  1.0f; writeToTextureQuad[16] =  1.0f; writeToTextureQuad[17] =  0.0f;
	writeToTextureQuad[18] =  1.0f; writeToTextureQuad[19] =  1.0f;
	

	
	writeToTextureIndices[0] = 0;
	writeToTextureIndices[1] = 1;
	writeToTextureIndices[2] = 2;
	writeToTextureIndices[3] = 0;
	writeToTextureIndices[4] = 2;
	writeToTextureIndices[5] = 3;
	
	
}

// For att kora denna maste indatan och utdatatexturen ha satts upp.
void GPUCollisionDetector::doCalculations(int nbrOfObjects,GLuint fb){
	
	glUseProgram(program);
	
	//glBindFramebuffer(GL_FRAMEBUFFER, fb);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//glViewport(0, 0, 320, 480);
	glViewport(0, 0, nbrOfObjects, nbrOfObjects);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	
	
	glVertexAttribPointer(a_position_loc, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), writeToTextureQuad);
	glEnableVertexAttribArray(a_position_loc);
	glVertexAttribPointer(a_texCoord_loc, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), &writeToTextureQuad[3]);
	glEnableVertexAttribArray(a_texCoord_loc);
	
	
	
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, writeToTextureIndices );
	
	
}

std::vector<std::pair<int,int> > GPUCollisionDetector::getCollidingObjects(int nbrOfObjects, GLubyte* collisionDetectionResult){
	
	std::vector<std::pair<int,int> > mayCollide;
	
	
	
	for (int i = 0; i<nbrOfObjects; i++) {
		for (int j = 0; j<nbrOfObjects; j++) {
			if (i<j && collisionDetectionResult[i*nbrOfObjects*4 + j*4] > 0) {
				mayCollide.push_back(std::make_pair(i,j));
				printf("\n%d och %d kolliderar",i,j);
			}
		}
	}
	
	return mayCollide;
}


/*
 for (int i = 0; i<nbrOfObjects; i++) {
 for (int j = 0; j<nbrOfObjects; j++) {
 if (collisionDetectionResult[nbrOfObjects*i + j*4] == 0) {
 mayCollide.push_back(i);
 break;
 }
 }
 }
 
 std::vector<int>::iterator start = mayCollide.begin();
 std::vector<int>::iterator end = mayCollide.end();
 
 printf("\n");
 for (; start!=end; start++) {
 printf("mayCollide %d ",*start);
 }
 printf("\n");
 */