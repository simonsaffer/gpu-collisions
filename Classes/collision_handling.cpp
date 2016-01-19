/*
 *  collision_handling.cpp
 *  ES1T
 *
 *  Created by Exjobb on 10/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "collision_handling.h"
#include <vector>
#include "sphere_detector.h"
#include <string>
#include <typeinfo>

CollisionHandler::CollisionHandler(std::vector<PhysicalObject> objects): objects(objects) {}

CollisionHandler::CollisionHandler() {}



CollisionHandler::~CollisionHandler(){
	delete detector;
	delete determinator;
	delete responder;
}

void CollisionHandler::doCollisionHandling(GLuint fb){
	
	
	std::vector<std::pair<int,int> > mayCollide = detector->doCollisionDetection(objects, fb);
	
	//printf("doCollisionHandling %d",(int) mayCollide.size());
	
	//std::vector<int> didCollide = determinator.doCollisionDetermination(objects,mayCollide);
	//responder.doCollisionResponse(objects,didCollide);
	
}