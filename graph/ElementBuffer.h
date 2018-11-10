#ifndef TINYENGINE_ELEMENTBUFFER_H
#define TINYENGINE_ELEMENTBUFFER_H


#include "VertexBufferBase.h"

namespace graph {

	class ElementBuffer :public VertexBufferBase
	{
	private:
		int _index_size;
	private:
		ElementBuffer(int indexSize) :VertexBufferBase(GL_ELEMENT_ARRAY_BUFFER) , _index_size(indexSize) {}

	public:
		static ElementBuffer * Create(int indexCount);
		static ElementBuffer * Create();

		void SetIndexSize(int indexSize){_index_size = indexSize;}
		int GetIndexSize(){return _index_size;}

		~ElementBuffer() = default;
	};
}

#endif