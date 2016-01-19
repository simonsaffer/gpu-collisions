/*
 *  obb_bounding_box.cpp
 *  Collision
 *
 *  Created by Exjobb on 10/30/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "obb_bounding_box.h"

OBBBoundingBox::OBBBoundingBox(){}

// This constructor could be used if one wanted to calculate a bb given 8 vertices
OBBBoundingBox::OBBBoundingBox(GLubyte* vertices){}

OBBBoundingBox::OBBBoundingBox(GLubyte* o, GLubyte* baseVectors, GLubyte* halfLengths) {
	for (int i = 0; i<4; i++) {
		origin[i] = o[i];
		baseVector1[i] = baseVectors[i];
		baseVector2[i] = baseVectors[i*2];
		baseVector3[i] = baseVectors[i*3];
	}
	
	halfLength1 = halfLengths[0];
	halfLength2 = halfLengths[1];
	halfLength3 = halfLengths[2];
}

OBBBoundingBox::OBBBoundingBox(GLubyte* o, GLubyte* bv1, GLubyte* bv2, GLubyte* bv3, GLubyte hl1, GLubyte hl2, GLubyte hl3) {
	for (int i = 0; i<4; i++) {
		origin[i] = o[i];
		baseVector1[i] = bv1[i];
		baseVector2[i] = bv2[i];
		baseVector3[i] = bv3[i];
	}
	
	halfLength1 = hl1;
	halfLength2 = hl2;
	halfLength3 = hl3;
}


OBBBoundingBox::~OBBBoundingBox(){}

