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
	    //编译shader并附加shader

	    if(_shaders.size() == 0)
	        return false;
		bool status = true;
		for (unsigned int i = 0; i < _shaders.size(); ++i)
		{
			bool is_success;
			Shader * shader = _shaders[i];
			if(!shader->IsCompile())
            {
                is_success = shader->Compile();
                status = status && is_success;
            }
            else
            {
                is_success = shader->IsAvailable();
                status = status && is_success;
            }
            if(status)
            {
                glAttachShader(_buffer_id, shader->GetBufferID());
            }
		}
		if (!status)
		{
			return false;
		}

		//链接Program
		glLinkProgram(_buffer_id);
		GLint is_success;
		glGetProgramiv(_buffer_id, GL_LINK_STATUS, &is_success);
		if (!is_success)
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
