/*
 *  textureHandler.cpp
 *  ES1T
 *
 *  Created by Exjobb on 9/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#include "textureHandler.h"



TextureHandler::TextureHandler(int nbrOfTextures): nbrOfActiveTextures(0) {
	
	textures = new GLuint[nbrOfTextures];
	textureProperties = new GLuint[nbrOfTextures*2];
	
}

TextureHandler::~TextureHandler(){
	delete[] textures;
	delete[] textureProperties;
}





	

