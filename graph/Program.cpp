#include "Program.h"

namespace graph
{



	Program::Program()
	{
		_buffer_id = glCreateProgram();
	}
	Program * Program::Creat(Shader * vs, Shader * fs)
	{
		auto * program = new Program();
		if (program->GetBufferID() == 0)
			return nullptr;

		if (vs->GetShaderType() != GL_VERTEX_SHADER && fs->GetShaderType() != GL_FRAGMENT_SHADER)
		{
			return nullptr;
		}
		program->AddShader(vs);
		program->AddShader(fs);
		return program;
	}
	Program * Program::Creat()
	{
		auto * program = new Program();
		if (program->GetBufferID() == 0)
			return nullptr;
		return program;
	}
	bool Program::Compile()
	{
	    //编译shader并附加shader
	    if(_shaders.empty())
	        return false;
		bool status = true;
		for(auto shader:_shaders)
		{
			bool is_success;
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
		GLint isSucceed;
		glGetProgramiv(_buffer_id, GL_LINK_STATUS, &isSucceed);
		if (!isSucceed)
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

	GLuint Program::GetBufferID() const
	{
		return _buffer_id;
	}

    Program::~Program()
    {
		glDeleteProgram(_buffer_id);
    }


    bool _compare_shader(Shader * shader, GLenum type)
	{
		return shader->GetShaderType() == type;
	}

}
