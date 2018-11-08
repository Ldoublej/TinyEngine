#ifndef BUFFER_DATA_HEADER
#define BUFFER_DATA_HEADER

#include <glad/glad.h>

namespace graph {

	class BufferData
	{
	protected:
		GLuint _buffer_id;
	private:
		GLenum _buffer_type;

		/*--------------------------------------------------------------------*/
	protected:
		BufferData(GLenum target)
		{
			_buffer_type = target;
			glGenBuffers(1, &_buffer_id);
		}

	public:
		
		GLuint GetBufferID()
		{
			return _buffer_id;
		}

		//BufferData�������ݲ���
		void SetData(GLsizeiptr size, const void * data, GLenum usage);
		void SetSubData(GLintptr offset, GLsizeiptr size, const void * data);
		void GetBufferSubData(GLintptr offset, GLsizeiptr size, void * data);

		void * MapBufferData(GLenum access);
		GLboolean UnmapBufferData();

		virtual ~BufferData() { glDeleteBuffers(1, &_buffer_id); };
	};
}

#endif