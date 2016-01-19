/*
 *  bounding_box.cpp
 *  ES1T
 *
 *  Created by Exjobb on 10/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "aabb_bounding_box.h"

AABBBoundingBox::AABBBoundingBox(GLfloat* vs) {
	for (int i = 0; i<8; i++) {
		vertices[i] = vs[i];
	}
}

AABBBoundingBox::AABBBoundingBox(){}