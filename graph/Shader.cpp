#include "Shader.h"

namespace graph
{
	Shader * Shader::Creat(GLenum type)
	{
		Shader * shader = new Shader(type);
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
	void Shader::Source(const std::string source)
	{
		const char * p[1];
		p[0] = source.c_str();
		int length = source.length();
		glShaderSource(_buffer_id, 1, p, &length);
	}
	bool Shader::Compile()
	{
		glCompileShader(_buffer_id);
		GLint isSucceess;
		glGetShaderiv(_buffer_id, GL_COMPILE_STATUS, &isSucceess);
		if (!isSucceess)
		{
			GLchar ch[1024];
			glGetShaderInfoLog(_buffer_id, 1024, NULL, ch);
			printf("%s", ch);
			return false;
		}
		return true;
	}
}