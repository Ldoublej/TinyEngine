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


		//*---------------------------------------------------------------*//
	public:
		static VertexArray * Create(ElementBuffer * ebo);
		void AddVertexBuffer(VertexBuffer * vbo);
		void SetElementBuffer(ElementBuffer * ebo);
		ElementBuffer * GetElementBuffer() const;
		VertexBuffer * GetVertexBuffer(int index);
        std::vector<graph::VertexBuffer *>::size_type GetVertexBufferCount() const;
		GLuint GetBufferID() const;
		void ApplyVertexAttributes();

	private:
		explicit VertexArray(ElementBuffer * ebo);

	};

}

#endif //SIMPLEOGL_VERTEXARRAY_H