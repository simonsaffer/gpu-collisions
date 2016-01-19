/*
 *  mesh.h
 *  ES1T
 *
 *  Created by Exjobb on 10/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __MESH_H__
#define __MESH_H__


#include <OpenGLES/ES2/gl.h>


class Mesh{
	
public:
	
	Mesh(GLfloat** positions, GLfloat** normals, GLushort** triangles, GLuint nbrOfIdx);
	Mesh();
	
	// Must be rendered as GL_TRIANGLES
	void makeMeACube(float size);
	// Must be rendered as GL_TRIANGLE_STRIP
	void makeMeASphere(float size, int resolution);
	

	//positioner
	GLfloat** positions;
	//normaler
	GLfloat** normals;
	// Antal triangelindex
	GLuint nbrOfIndices;
	//triangelIndex
	GLushort** triangles;
	// Texturkoordinater
	GLfloat** texCoords;

};
#endif