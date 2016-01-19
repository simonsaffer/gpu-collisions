/*
 *  mesh.cpp
 *  ES1T
 *
 *  Created by Exjobb on 10/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "mesh.h"
#include "esUtil.h"

Mesh::Mesh(GLfloat** positions, GLfloat** normals, GLushort** triangles, GLuint nbrOfIdx): positions(positions), normals(normals), triangles(triangles), nbrOfIndices(nbrOfIdx), texCoords(0) {}

Mesh::Mesh(): positions(0), normals(0), triangles(0), nbrOfIndices(0), texCoords(0) {}

void Mesh::makeMeACube(float size){
	nbrOfIndices = esGenCube(size, positions, normals, texCoords, triangles);
}

void Mesh::makeMeASphere(float size, int resolution){
	nbrOfIndices = esGenSphere(resolution, size, positions, normals, texCoords, triangles);
}