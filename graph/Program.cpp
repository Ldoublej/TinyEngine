#include "Program.h"

namespace graph
{



	Program::Program()
	{
		_buffer_id = glCreateProgram();
	}
	Program * Program::Creat(Shader * vs, Shader * fs)
	{
		Program * pro = new Program();
		if (pro->GetBufferID() == 0)
			return nullptr;

		if (vs->GetShaderType() != GL_VERTEX_SHADER && fs->GetShaderType() != GL_FRAGMENT_SHADER)
		{
			return nullptr;
		}
		pro->AddShader(vs);
		pro->AddShader(fs);
		return pro;
	}
	Program * Program::Creat()
	{
		Program * pro = new Program();
		if (pro->GetBufferID() == 0)
			return nullptr;
		return pro;
	}
	bool Program::Compile()
	{
		bool status = true;
		for (unsigned int i = 0; i < _shaders.size(); ++i)
		{
			bool isSuccess;
			isSuccess = _shaders[i]->Compile();
			status = status && isSuccess;
			if(isSuccess)
				glAttachShader(_buffer_id, _shaders[i]->GetBufferID());
		}
		if (!status)
		{
			return false;
		}

		glLinkProgram(_buffer_id);
		GLint isSuccess;
		glGetProgramiv(_buffer_id, GL_LINK_STATUS, &isSuccess);
		if (!isSuccess)
		{
			GLchar ch[1024];
			glGetProgramInfoLog(_buffer_id, 1024, NULL, ch);
			printf("%s", ch);
			return false;
		}
		_is_compile = true;
		return true;
	}
	Shader * Program::GetShader(GLenum type)
	{
		auto it = std::find_if(_shaders.begin(), _shaders.end(), std::bind(_compare_shader, std::placeholders::_1,type) );
		if (it != _shaders.end())
		{
			return (*it);
		}
		return nullptr;
	}

	void Program::AddShader(Shader * shader)
	{
		auto it = std::find_if(_shaders.begin(), _shaders.end(), std::bind(_compare_shader, std::placeholders::_1, shader->GetShaderType()));
		if (it != _shaders.end())
		{
			*it = shader;
		}
		else
		{
			_shaders.push_back(shader);
		}
	}



	bool _compare_shader(Shader * shader, GLenum type)
	{
		if (shader->GetShaderType() != type)
			return false;
		return true;
	}

}
