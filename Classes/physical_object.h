/*
 *  physical_object.h
 *  ES1T
 *
 *  Created by Exjobb on 10/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PHYSICAL_OBJECT__
#define __PHYSICAL_OBJECT__

#include <OpenGLES/ES2/gl.h>
#include "esUtil.h"
#include "mesh.h"
//#include "bounding_box.h"
#include "bounding_sphere.h"
#include "obb_bounding_box.h"



class PhysicalObject{

public:
	
	PhysicalObject();
	
	PhysicalObject(Mesh mesh, OBBBoundingBox bb, BoundingSphere bs);
	
	void addForce(GLfloat* direcion, GLuint intensity);
	
	void isAffectedByGravity(bool val);
	
	Mesh mesh;
	OBBBoundingBox bb;
	bool gravity;
	ESMatrix transform; // Transformation matrix for both mesh and boundingbox
	GLfloat velocity[3]; // Kan ge problem?
	BoundingSphere boundingSphere;
	
};

#endif