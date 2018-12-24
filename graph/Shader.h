#ifndef SIMPLEOGL_SHADER_H
#define SIMPLEOGL_SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>

namespace graph
{
	class Shader
	{
	private:
		GLuint _buffer_id; //buffer id 由 glGen*类函数生成
		GLenum _shader_type; //shader的类型,比如 vs(VertexShader) 或者 fs(FragmentShader)
		bool _is_compile; //是否进行过编译
		bool _is_succeed; //编译是否成功
		std::string _content;
	private:
		explicit Shader(GLenum type) :_shader_type(type),_is_compile(false),_is_succeed(false) {_buffer_id = glCreateShader(_shader_type);}


	public:
		static Shader * Creat(GLenum type);
		static Shader * Creat(GLenum type,const char * filename);



		void Source(const std::string & source);
		bool Compile();
		bool IsCompile() const;
		bool IsAvailable() const;
		GLuint GetBufferID() const;
		GLenum GetShaderType() const;

		~Shader();
	};
}

#endif//SIMPLEOGL_SHADER_H