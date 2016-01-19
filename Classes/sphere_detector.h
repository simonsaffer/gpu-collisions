/*
 *  sphere_detector.h
 *  Collision
 *
 *  Created by Exjobb on 10/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __SPHERE_DETECTOR__
#define __SPHERE_DETECTOR__


#include "gpu_collision_detector.h"
#include "physical_object.h"
#include <vector>


class SphereDetector: public GPUCollisionDetector{

public:
	
	SphereDetector(GLuint program, int nbrOfObjects);
	
	virtual std::vector<std::pair<int,int> > doCollisionDetection(std::vector<PhysicalObject>& objects,GLuint fb);
	
	
	
};

#endif