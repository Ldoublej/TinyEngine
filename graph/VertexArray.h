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
		ElementBuffer * _ebo;

	private:

		explicit VertexArray(ElementBuffer * ebo);

	public:
		static VertexArray * Create(ElementBuffer * ebo);

		GLuint GetBufferID()
		{
			return _buffer_id;
		}


		void AddVertexBuffer(VertexBuffer * vbo);

		void SetElementBuffer(ElementBuffer * ebo);
		ElementBuffer * GetElementBuffer() { return _ebo; }

		VertexBuffer * GetVertexBuffer(int index);
		int GetVertexBufferCount() { return _vbo_list.size(); }

		void ApplyVertexAttributes();


	};

}

#endif //SIMPLEOGL_VERTEXARRAY_H