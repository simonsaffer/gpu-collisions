/*
 *  collision_handling.h
 *  ES1T
 *
 *  Created by Exjobb on 10/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __COLLISION_HANDLER__
#define __COLLISION_HANDLER__


#include "physical_object.h"
#include <vector>


class CollisionDetector{
	
public:
	
	// This implements the broad phase in collision handling
	// Returns a list with indices for the objects that might have collided
	virtual std::vector<std::pair<int,int> > doCollisionDetection(std::vector<PhysicalObject>& objects,GLuint fb){
		assert(false);
		std::vector<std::pair<int,int> > v;
		return v;};
	
};





class CollisionDeterminator{
	
public:
	
	// This implements the narrow phase in collision handling
	// Returns a list with indices for the objects that have collided
	virtual std::vector<int> doCollisionDetermination(std::vector<PhysicalObject>& objects, std::vector<int>& mayCollide){assert(false);std::vector<int> v;return v;};
	
};



class CollisionResponder{
	
public:
	
	// Takes a list of the objects that have collided and calculates the new velocities
	// given the positions, masses and previos velocities of the colliding objects
	virtual void doCollisionResponse(std::vector<PhysicalObject>& objects, std::vector<int>& didCollide){};
	
};



class CollisionHandler{
	
public:
	
	CollisionHandler();
	
	CollisionHandler(std::vector<PhysicalObject> objects);
	
	//CollisionHandler(const char* vShaderPath, const char* fShaderPath, std::vector<PhysicalObject>& objects);
	
	~CollisionHandler();
	
	
	
	void doCollisionHandling(GLuint fb);
	
	std::vector<PhysicalObject> objects;
	
	
	CollisionDetector* detector;
	CollisionDeterminator* determinator;
	CollisionResponder* responder;
	
	
	// Forbidden
	void operator= (CollisionHandler&);
	
};


#endif