#include "BufferData.h"

namespace graph {



	void BufferData::SetData(GLsizeiptr size, const void * data, GLenum usage)
	{
		glBindBuffer(_buffer_type, _buffer_id);
		glBufferData(_buffer_type, size, data, usage);
		glBindBuffer(_buffer_type, 0);
	}

	void BufferData::SetSubData(GLintptr offset, GLsizeiptr size, const void * data)
	{
		glBindBuffer(_buffer_type, _buffer_id);
		glBufferSubData(_buffer_type, offset, size, data);
		glBindBuffer(_buffer_type, 0);
	}

	void BufferData::GetBufferSubData(GLintptr offset, GLsizeiptr size, void * data)
	{
		glBindBuffer(_buffer_type, _buffer_id);
		glGetBufferSubData(_buffer_type, offset, size, data);
		glBindBuffer(_buffer_type, 0);
	}

	void * BufferData::MapBufferData(GLenum access)
	{
		glBindBuffer(_buffer_type, _buffer_id);
		void * d = glMapBuffer(_buffer_type, access);
		glBindBuffer(_buffer_type, 0);
		return d;

	}

	GLboolean BufferData::UnmapBufferData()
	{
		glBindBuffer(_buffer_type, _buffer_id);
		GLboolean b =  glUnmapBuffer(_buffer_type);
		glBindBuffer(_buffer_type, 0);
		return b;
	}

}