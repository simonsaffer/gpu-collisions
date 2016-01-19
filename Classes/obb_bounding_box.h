/*
 *  obb_bounding_box.h
 *  Collision
 *
 *  Created by Exjobb on 10/30/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __OBB_BOUNDING_BOX__
#define __OBB_BOUNDING_BOX__

#include <OpenGLES/ES2/gl.h>
#include "bounding_box.h"

class OBBBoundingBox: public BoundingBox{
	
public:
	
	OBBBoundingBox();
	OBBBoundingBox(GLubyte* vertices);
	OBBBoundingBox(GLubyte* origin, GLubyte* baseVectors, GLubyte* halfLengths);
	OBBBoundingBox(GLubyte* origin, GLubyte* baseVector1, GLubyte* baseVector2, GLubyte* baseVector3, GLubyte halfLength1, GLubyte halfLength2, GLubyte halfLength3);
	~OBBBoundingBox();
	
	GLubyte origin[4];
	GLubyte baseVector1[4];
	GLubyte baseVector2[4]; 
	GLubyte baseVector3[4]; 
	GLubyte halfLength1; 
	GLubyte halfLength2; 
	GLubyte halfLength3;
	
	
};

#endif
