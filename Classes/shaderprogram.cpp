#include "shaderprogram.h"
#include <iostream>
#include <fstream>


using namespace std;


namespace eswin{
	ShaderProgram::ShaderProgram(){
	}


	void ShaderProgram::deleteProgram(){
		glDeleteProgram(m_program);
		m_program=0;
	}

	void ShaderProgram::useProgram() const{
		glUseProgram(m_program);
	}

	GLboolean ShaderProgram::loadProgramFromSource(const char *vshaderPath, const char *fshaderPath){
		GLuint vshader,fshader;
		if(!loadShader(vshaderPath,GL_VERTEX_SHADER,vshader)){
			return GL_FALSE;
		}
		if(!loadShader(fshaderPath,GL_FRAGMENT_SHADER,fshader)){
			return GL_FALSE;
		}
		
		m_program=glCreateProgram();
	
		if(!m_program){
			return GL_FALSE;
		}

		glAttachShader(m_program,vshader);
		glAttachShader(m_program,fshader);
	
		//bind...

		glLinkProgram(m_program);


		GLint linked;
		glGetProgramiv(m_program,GL_LINK_STATUS,&linked);
		if(!linked){
			return GL_FALSE;
		}

		return GL_TRUE;
	}

	GLboolean ShaderProgram::loadShader(const char *filename, GLenum type,GLuint &shader){
		shader=glCreateShader(type);
		if(shader==0){
			return GL_FALSE;
		}

		ifstream file;
		file.open(filename,fstream::in);
		if(!file.is_open()){
			cout << "can't find "<<filename<<endl;
			return GL_FALSE;
		}
		
		int length;
		file.seekg(0,ios::end);
		length=file.tellg();
		file.seekg(0,ios::beg);
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
			cout << log << endl;
			delete[] log;

			return GL_FALSE;
		}
		
		return GL_TRUE;

	}

}