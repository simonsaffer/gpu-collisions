/*
 *  physical_object.cpp
 *  ES1T
 *
 *  Created by Exjobb on 10/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#include "physical_object.h"
#include "mesh.h"
#include "bounding_box.h"



PhysicalObject::PhysicalObject(Mesh mesh, OBBBoundingBox bb, BoundingSphere bs): mesh(mesh), bb(bb), gravity(true), boundingSphere(bs) {
	esMatrixLoadIdentity(&transform); // Initiate the transform matrix as the identity matrix
	velocity[0] = 0.0; velocity[2] = 0.0; velocity[2] = 0.0;
}

PhysicalObject::PhysicalObject(): gravity(true) {
	esMatrixLoadIdentity(&transform);
	velocity[0] = 0.0; velocity[2] = 0.0; velocity[2] = 0.0;
}