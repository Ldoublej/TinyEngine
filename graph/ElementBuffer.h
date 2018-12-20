#ifndef SIMPLEOGL_ELEMENTBUFFER_H
#define SIMPLEOGL_ELEMENTBUFFER_H


#include "VertexBufferBase.h"

namespace graph {

	class ElementBuffer :public VertexBufferBase
	{
	private:
		ElementBuffer() :VertexBufferBase(GL_ELEMENT_ARRAY_BUFFER){}

	public:
		static ElementBuffer * Create();
		~ElementBuffer() = default;
	};
}

#endif  //SIMPLEOGL_ELEMENTBUFFER_H