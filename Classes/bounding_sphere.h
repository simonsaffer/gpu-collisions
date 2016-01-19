/*
 *  bounding_sphere.h
 *  Collision
 *
 *  Created by Exjobb on 10/30/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

// Can contain an object origin and a radius
class BoundingSphere{
	
public:
	
	BoundingSphere(GLubyte x, GLubyte y, GLubyte z, GLubyte r): x(x), y(y), z(z), r(r) {}
	BoundingSphere(): x(0), y(0), z(0), r(0) {}
	
	GLfloat x,y,z,r;
};