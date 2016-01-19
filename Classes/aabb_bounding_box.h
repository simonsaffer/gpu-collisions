/*
 *  bounding_box.h
 *  ES1T
 *
 *  Created by Exjobb on 10/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __AABB_BOUNDING_BOX__
#define __AABB_BOUNDING_BOX__

#include <OpenGLES/ES2/gl.h>
#include "bounding_box.h"


class AABBBoundingBox: public BoundingBox{

public:
	
	AABBBoundingBox();
	
	AABBBoundingBox(GLfloat* vertices);
	
	//8 positioner
	GLfloat vertices[8];

};
#endif