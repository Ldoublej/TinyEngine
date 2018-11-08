#ifndef TINYENGINE_SHADER_H
#define TINYENGINE_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>

namespace graph
{
	class Shader
	{
	private:
		GLuint _buffer_id;
		GLenum _shader_type;
	private:
		Shader(GLenum type) :_shader_type(type) {_buffer_id = glCreateShader(_shader_type);}

	public:
		static Shader * Creat(GLenum type);
		static Shader * Creat(GLenum type,const char * filename);


		void Source(const std::string source);
		bool Compile();
		GLuint GetBufferID(){return _buffer_id;}
		GLenum GetShaderType() {return _shader_type;}

		~Shader()
		{
			glDeleteShader(_buffer_id);
		}
	};
}

#endif