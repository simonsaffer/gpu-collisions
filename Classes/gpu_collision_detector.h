/*
 *  gpu_collision_detector.h
 *  Collision
 *
 *  Created by Exjobb on 10/8/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __GPU_COLLISIONDETECTOR__
#define __GPU_COLLISIONDETECTOR__


#include "collision_handling.h"
#include "textureHandler.h"


class GPUCollisionDetector : public CollisionDetector {
	
public:
	
	GPUCollisionDetector(GLuint program, int nbrOfObjects);
	
	virtual std::vector<std::pair<int,int> > doCollisionDetection(std::vector<PhysicalObject>& objects,GLuint fb){
		assert(false);
		std::vector<std::pair<int,int> > v;
		return v;}
	
	void doCalculations(int nbrOfObjects ,GLuint fb);
	
	std::vector<std::pair<int,int> > getCollidingObjects(int nbrOfObjects,GLubyte* collisionDetectionResult);
	
	
protected:
	
	GLuint framebuffer;
	
	TextureHandler texHandler;
	
	GLuint program;
	
	GLuint a_position_loc, a_texCoord_loc, s_srcTex_loc;
	
	GLuint in_data;
	GLuint result;
	
	GLubyte* theInData;
	GLubyte* collisionDetectionResult;
	
	
	static GLfloat writeToTextureQuad[20];
	static GLushort writeToTextureIndices[6];
	
	
};

#endif