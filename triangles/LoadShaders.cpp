//////////////////////////////////////////////////////////////////////////////
//
//  --- LoadShaders.cxx ---
//
//////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include "LoadShaders.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	//----------------------------------------------------------------------------

	static const GLchar*
		ReadShader(const char* filename)
	{
#ifdef WIN32
		FILE* infile;
		fopen_s(&infile, filename, "rb");
#else
		FILE* infile = fopen(filename, "rb");
#endif // WIN32

		if (!infile) {
#ifdef _DEBUG
			std::cerr << "Unable to open the fucking file '" << filename << "'" << std::endl;
#endif /* DEBUG */
			return NULL;
		}

		fseek(infile, 0, SEEK_END);
		int len = ftell(infile);
		fseek(infile, 0, SEEK_SET);

		GLchar* source = new GLchar[len + 1];

		fread(source, 1, len, infile);
		fclose(infile);

		source[len] = 0;

		return const_cast<const GLchar*>(source);
	}

	//----------------------------------------------------------------------------

	GLuint
		LoadShaders(ShaderInfo* shaders)
	{
		if (shaders == NULL) { return 0; }	// if no shaders specified, then exit

		GLuint program = glCreateProgram(); // glCreateProgram creates an empty program object and returns a non zero value by
											// which it can be referenced

		ShaderInfo* entry = shaders;


		while (entry->type != GL_NONE)		// loop on the shaders, till you get to a shader struct whose type is GL_NONE
		{

			//glCreateShader creates an empty shader object with the type specified in the 
			//shaderinfo structure, returns a non zero value by which it can be referenced
			GLuint shader = glCreateShader(entry->type);

			//copy the reference returned by glCreateShader, into the 'shader' variable of the shaderinfo struct 
		    entry->shader = shader;	//notice that the 'shader' in shaderinfo struct wasnt defined in the init func in source/main.cpp

			const GLchar* source = ReadShader(entry->filename); // point source to the filename in shaderinfo struct 

			// if the filename of the shaderinfo struct you are currently reading is NULL then delete all following shaders 
			//till you get to a shader whose type value in the shaderinfo struct is GL_NONE, and then exit
			if (source == NULL) 
			{
				for (entry = shaders; entry->type != GL_NONE; ++entry) 
				{
					glDeleteShader(entry->shader);
					entry->shader = 0;
				}

				return 0; // exit
			}

			glShaderSource(shader, 1, &source, NULL); //http://stackoverflow.com/questions/22100408/what-is-the-meaning-of-the-parameters-to-glshadersource 
			delete[] source;

			glCompileShader(shader);	// compile the shader
										
										// check for compiling errors, display log if failed and exit
			GLint compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); //returns compile status of the shader via 
																//'compiled' variable (either GL_TRUE or GL_FALSE)
			
			if (!compiled) 
			{
#ifdef _DEBUG
				GLsizei len;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

				GLchar* log = new GLchar[len + 1];
				glGetShaderInfoLog(shader, len, &len, log);
				std::cerr << "Shader compilation failed: " << log << std::endl;
				delete[] log;
#endif /* DEBUG */

				return 0; //exit
			}

			glAttachShader(program, shader);	//finally attach it to the program when no errors

			++entry; //go to the next entry in "ShaderInfo shaders[]" in init function in main.cpp/source.cpp
		}

#ifdef GL_VERSION_4_1
		if (GLEW_VERSION_4_1) {
			// glProgramParameteri( program, GL_PROGRAM_SEPARABLE, GL_TRUE );
		}
#endif /* GL_VERSION_4_1 */

		glLinkProgram(program);	//link the shader

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked); //check for linking errors
		
		if (!linked)  //if linking fails, display log and delete shader 
		{
#ifdef _DEBUG
			GLsizei len;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, &len, log);
			std::cerr << "Shader linking failed: " << log << std::endl;
			delete[] log;


#endif /* DEBUG */

			for (entry = shaders; entry->type != GL_NONE; ++entry) 
			{
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			return 0;
		}

		return program;
	}

	//----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus

