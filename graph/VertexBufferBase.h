#ifndef SIMPLEOGL_VERTEXBUFFERBASE_H
#define SIMPLEOGL_VERTEXBUFFERBASE_H

#include <glad/glad.h>

namespace graph {

	class VertexBufferBase
	{
	protected:
		GLuint _buffer_id;
	private:
		GLenum _buffer_type;

		/*--------------------------------------------------------------------*/
	protected:
		VertexBufferBase(GLenum target)
		{
			_buffer_type = target;
			glGenBuffers(1, &_buffer_id);
		}

	public:
		
		GLuint GetBufferID()
		{
			return _buffer_id;
		}

		//Buffer数据操作
		void SetData(GLsizeiptr size, const void * data, GLenum usage);
		void SetSubData(GLintptr offset, GLsizeiptr size, const void * data);
		void GetBufferSubData(GLintptr offset, GLsizeiptr size, void * data);

		void * MapBufferData(GLenum access);
		GLboolean UnmapBufferData();

		virtual ~VertexBufferBase() { glDeleteBuffers(1, &_buffer_id); };
	};
}

#endif //SIMPLEOGL_VERTEXBUFFERBASE_H