#include "ElementBuffer.h"

namespace graph {


	ElementBuffer * ElementBuffer::Create()
	{
		auto * ebo = new ElementBuffer();
		if (ebo->GetBufferID() == 0)
			return nullptr;
		return ebo;
	}
}
