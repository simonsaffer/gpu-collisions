/*
 *  obb_detector.h
 *  Collision
 *
 *  Created by Exjobb on 10/30/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __OBB_DETECTOR__
#define __OBB_DETECTOR__

#include "gpu_collision_detector.h"

class OBBDetector: public GPUCollisionDetector{
	
public:
	
	OBBDetector(GLuint program, int nbrOfObjects);
	
	virtual std::vector<std::pair<int,int> > doCollisionDetection(std::vector<PhysicalObject>& objects,GLuint fb);
	
	GLuint u_nbrOfObjects_loc, u_transform_loc;
	
	
};

#endif