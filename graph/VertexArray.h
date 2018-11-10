#ifndef SIMPLEOGL_VERTEXARRAY_H
#define SIMPLEOGL_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "ElementBuffer.h"

namespace graph{


	class VertexArray
	{
	private:
		GLuint _buffer_id;
		std::vector<VertexBuffer *> _vbo_list;
		GLenum _primitive_type;
		ElementBuffer * _ebo;

	private:
		VertexArray(GLenum primitiveType, ElementBuffer * ebo);

	public:
		static VertexArray * Create(GLenum primitiveType, ElementBuffer * ebo);

		GLuint GetBufferID()
		{
			return _buffer_id;
		}
		GLenum GetPrimitiveType()
		{
			return _primitive_type;
		}

		void AddVertexBuffer(VertexBuffer * vbo);
		ElementBuffer * GetElementBuffer() { return _ebo; }
		VertexBuffer * GetVertexBuffer(int index);
		int GetVertexBufferCount() { return _vbo_list.size(); }

		void ApplyVertexAttributes();
		void AddElementBuffer(ElementBuffer * ebo);

	};

}

#endif //SIMPLEOGL_VERTEXARRAY_H