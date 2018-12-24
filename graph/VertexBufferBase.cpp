#include "VertexBufferBase.h"

namespace graph {



	void VertexBufferBase::SetData(GLsizeiptr size, const void * data, GLenum usage)
	{
		glBindBuffer(_buffer_type, _buffer_id);
		glBufferData(_buffer_type, size, data, usage);
		glBindBuffer(_buffer_type, 0);
	}

	void VertexBufferBase::SetSubData(GLintptr offset, GLsizeiptr size, const void * data)
	{
		glBindBuffer(_buffer_type, _buffer_id);
		glBufferSubData(_buffer_type, offset, size, data);
		glBindBuffer(_buffer_type, 0);
	}

	void VertexBufferBase::GetBufferSubData(GLintptr offset, GLsizeiptr size, void * data)
	{
		glBindBuffer(_buffer_type, _buffer_id);
		glGetBufferSubData(_buffer_type, offset, size, data);
		glBindBuffer(_buffer_type, 0);
	}

	void * VertexBufferBase::MapBufferData(GLenum access)
	{
		glBindBuffer(_buffer_type, _buffer_id);
		void * d = glMapBuffer(_buffer_type, access);
		glBindBuffer(_buffer_type, 0);
		return d;

	}

	GLboolean VertexBufferBase::UnmapBufferData()
	{
		glBindBuffer(_buffer_type, _buffer_id);
		GLboolean b =  glUnmapBuffer(_buffer_type);
		glBindBuffer(_buffer_type, 0);
		return b;
	}

	VertexBufferBase::~VertexBufferBase()
	{
		glDeleteBuffers(1, &_buffer_id);
	}

}