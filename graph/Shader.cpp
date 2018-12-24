#include "Shader.h"

namespace graph
{
	Shader * Shader::Creat(GLenum type)
	{
		auto * shader = new Shader(type);
		if (shader->GetBufferID() == 0)
			return nullptr;

		return shader;
	}

	Shader * Shader::Creat(GLenum type, const char * filename)
	{
		
		Shader * shader = Shader::Creat(type);
		using namespace std;

		ifstream infile;
		infile.open(filename);
		string c;
		string s;
		while (getline(infile, s))
		{
			c.append(s);
			c.append("\n");
		}
		infile.close();

		shader->Source(c);
		return shader;
	}

	void Shader::Source(const std::string & source)
	{
		const char * p[1];
		p[0] = source.c_str();
		int length = static_cast<int>(source.length());
		glShaderSource(_buffer_id, 1, p,&length);
		_content.clear();
		_content = source;
	}

	bool Shader::Compile()
	{
		glCompileShader(_buffer_id);
		GLint isSucceed;
		glGetShaderiv(_buffer_id, GL_COMPILE_STATUS, &isSucceed);
		if (!isSucceed)
		{
			GLchar ch[1024];
			glGetShaderInfoLog(_buffer_id, 1024, nullptr, ch);
			printf("%s", ch);
			return false;
		}
        _is_compile = true;
		_is_succeed = true;
		return true;
	}

	bool Shader::IsCompile() const
	{
		return _is_compile;
	}

	bool Shader::IsAvailable() const
	{
		return _is_succeed;
	}

	GLuint Shader::GetBufferID() const
	{
		return _buffer_id;
	}

	GLenum Shader::GetShaderType() const
	{
		return _shader_type;
	}

	Shader::~Shader()
	{
		glDeleteShader(_buffer_id);
	}
}