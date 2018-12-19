#ifndef SIMPLEOGL_PROGRAM_H
#define SIMPLEOGL_PROGRAM_H

#include "Shader.h"
#include <vector>
#include <functional>
#include <algorithm>

namespace graph
{
	bool _compare_shader(Shader * shader, GLenum type);

	class Program
	{
	private:
		GLuint _buffer_id;
		std::vector<Shader *> _shaders;
		bool _is_compile;
	private:
		Program();

	public:
		static Program * Creat(Shader * vs, Shader * fs);
		static Program * Creat();

		void AddShader(Shader * shader);
		Shader * GetShader(GLenum type);

		bool Compile();

		void Unifrom1i(const char * uniform,GLint v0);
		void Unifrom4fv(const char * uniform,const GLfloat * mat4);
		GLuint GetBufferID(){return _buffer_id;}


		~Program()
		{
			glDeleteProgram(_buffer_id);
		}

	
	};

}

#endif	//SIMPLEOGL_PROGRAM_H