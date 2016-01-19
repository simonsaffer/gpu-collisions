/*
 *  shader_util.h
 *  Collision
 *
 *  Created by Exjobb on 10/20/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>


GLboolean loadShader(const char *filename, GLenum type,GLuint &shader){
	
	shader=glCreateShader(type);
	if(shader==0){
		return GL_FALSE;
	}
	
	std::ifstream file;
	file.open(filename,std::fstream::in);
	if(!file.is_open()){
		std::cout << "can't find "<<filename<< std::endl;
		return GL_FALSE;
	}
	
	int length;
	file.seekg(0,std::ios::end);
	length=file.tellg();
	file.seekg(0,std::ios::beg);
	char *buffer=new char[length+1];
	if(!buffer){ //out of mem
		file.close();
		return GL_FALSE;
	}
	
	file.read(buffer,length);
	int readLength=file.gcount();
	buffer[readLength]='\0';
	file.close();
	
	
	glShaderSource(shader,1,(const char **)&buffer,NULL);
	delete[] buffer;
	
	glCompileShader(shader);
	
	int compiled;
	
	glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
	
	if(!compiled){
		
		GLint infoLen=0;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infoLen);
		char *log=new char[infoLen];
		glGetShaderInfoLog(shader,infoLen,&infoLen,log);
		std::cout << log << std::endl;
		delete[] log;
		
		return GL_FALSE;
	}
	
	return GL_TRUE;
	
}



GLuint loadProgram ( const char *vertShaderPath, const char *fragShaderPath )
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLboolean compiled;
	GLint linked;
	
	
	// Load the vertex/fragment shaders
	compiled = loadShader(vertShaderPath, GL_VERTEX_SHADER, vertexShader);
	if ( compiled == 0 )
		return 0;
	
	compiled = loadShader(fragShaderPath, GL_FRAGMENT_SHADER, fragmentShader );
	if ( compiled == 0 )
	{
		glDeleteShader( vertexShader );
		return 0;
	}
	
	// Create the program object
	programObject = glCreateProgram();
	
	if ( programObject == 0 )
		return 0;
	
	glAttachShader ( programObject, vertexShader );
	glAttachShader ( programObject, fragmentShader );
	
	// Link the program
	glLinkProgram ( programObject );
	
	// Check the link status
	glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );
	
	if ( !linked ) 
	{
		GLint infoLen = 0;
		
		glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
		
		if ( infoLen > 1 )
		{
			char* infoLog = (char*) malloc (sizeof(char) * infoLen );
			
			glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
			printf( "Error linking program:\n%s\n", infoLog );            
			
			free ( infoLog );
		}
		
		glDeleteProgram ( programObject );
		return 0;
	}
	
	// Free up no longer needed shader resources
	glDeleteShader ( vertexShader );
	glDeleteShader ( fragmentShader );
	
	return programObject;
}