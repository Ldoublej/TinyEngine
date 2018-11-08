#include "ElementBuffer.h"

namespace graph {


	ElementBuffer * ElementBuffer::Create(int indexSize)
	{
		ElementBuffer * ebo = new ElementBuffer(indexSize);
		if (ebo->GetBufferID() == 0)
			return nullptr;
		return ebo;
	}

	ElementBuffer * ElementBuffer::Create()
	{
		ElementBuffer * ebo = new ElementBuffer(0);
		if (ebo->GetBufferID() == 0)
			return nullptr;
		return ebo;
	}


}
