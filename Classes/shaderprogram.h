#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#ifdef _WIN32
	#include <GLES2/gl2.h>
#elif
	#include <apples/coola/gles2/path.h> 
#endif

namespace eswin{

	class ShaderProgram
	{
	public:
		ShaderProgram();
		//in: path to the source of the shaders
		//out: true if succesfully loaded, otherwise false
		GLboolean loadProgramFromSource(const char* vshader,const char* fshader);

		void deleteProgram();

		//glUseProgram....
		void useProgram() const;

		GLuint getProgram(){return m_program;};
		
		
	private:
		GLuint m_program;

		GLboolean loadShader(const char* filename,GLenum type,GLuint &shader);
		
	};

}


#endif