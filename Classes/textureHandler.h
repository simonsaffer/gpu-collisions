/*
 *  textureHandler.h
 *  ES1T
 *
 *  Created by Exjobb on 9/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __TEXTURE_HANDLER__
#define __TEXTURE_HANDLER__


#include <OpenGLES/ES2/gl.h>
#include <stdio.h>
#include <assert.h>


class TextureHandler{

public:
	
	// Constructor
	TextureHandler(int nbrOfTextures);
	
	//Destructor
	~TextureHandler();
	
	// Returns a pointer to the texture that holds the values of the array
	template <class T>
	GLuint createArray(int width, int height, T *arrayValues);
	
	
	// Get the values for a given texture
	template <class T>
	void getArray(GLuint texture, T *arrayValues);
	
	
private:
	
	GLuint *textures; // Pointers to all the textures used to implement arrays
	GLuint *textureProperties; // width and height for all textures
	GLuint nbrOfActiveTextures; // The number of textures that have been registered
	
	
};

// Returns a pointer to the texture that holds the values of the array
template <class T>
GLuint TextureHandler::createArray(int width, int height, T *arrayValues){
	
	GLuint tex;
	glGenTextures(1, &tex);
	glActiveTexture( GL_TEXTURE0 + nbrOfActiveTextures );
	glBindTexture( GL_TEXTURE_2D, tex );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	
	if (arrayValues != 0) {
		GLubyte* pBytePointer = (GLubyte*)(arrayValues);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBytePointer);
	}else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	}
	
	
	textures[nbrOfActiveTextures] = tex;
	textureProperties[nbrOfActiveTextures*2] = width;
	textureProperties[nbrOfActiveTextures*2 + 1] = height;
	nbrOfActiveTextures++;
	
	
	return tex;
	
}


// Get the values from a given texture
template <class T>
void TextureHandler::getArray(GLuint texture,T* arrayValues){
	
	int i = 0;
	while (i<nbrOfActiveTextures) {
		if (textures[i] == texture) {
			break;
		}
		i++;
	}
	
	// Info for width/height are in textureProperties[2*i]/textureProperties[2*i+1]
	int w = textureProperties[2*i];
	int h = textureProperties[2*i+1];
	
	
	GLubyte *out_data = (GLubyte*) arrayValues;
	
	glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, out_data);

	
}

#endif