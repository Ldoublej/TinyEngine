#include "Program.h"

namespace graph
{



	Program::Program()
	{
		_buffer_id = glCreateProgram();
	}
	Program * Program::Creat(Shader * vs, Shader * fs)
	{
		auto * pro = new Program();
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
		auto * pro = new Program();
		if (pro->GetBufferID() == 0)
			return nullptr;
		return pro;
	}
	bool Program::Compile()
	{
	    //编译shader并附加shader

	    if(_shaders.empty())
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
			glGetProgramInfoLog(_buffer_id, 1024, nullptr, ch);
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

    void Program::Unifrom1i(const char *uniform, GLint v0)
    {
		GLint currentProgram = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM,&currentProgram);

		if(currentProgram != _buffer_id)
		{
			glUseProgram(_buffer_id);
		}
		GLint id = glGetUniformLocation(this->_buffer_id,uniform);
		glUniform1i(id,v0);
		if(currentProgram != _buffer_id)
		{
			glUseProgram(currentProgram);
		}
    }

	void Program::Unifrom4fv(const char *uniform, const GLfloat * mat4)
	{
		GLint currentProgram = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM,&currentProgram);

		if(currentProgram != _buffer_id)
		{
			glUseProgram(_buffer_id);
		}
		GLint id = glGetUniformLocation(this->_buffer_id,uniform);
		glUniformMatrix4fv(id,1,GL_FALSE,mat4);
		if(currentProgram != _buffer_id)
		{
			glUseProgram(currentProgram);
		}
	}


	bool _compare_shader(Shader * shader, GLenum type)
	{
		if (shader->GetShaderType() != type)
			return false;
		return true;
	}

}
