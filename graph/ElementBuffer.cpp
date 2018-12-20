#include "ElementBuffer.h"

namespace graph {


	ElementBuffer * ElementBuffer::Create()
	{
		ElementBuffer * ebo = new ElementBuffer();
		if (ebo->GetBufferID() == 0)
			return nullptr;
		return ebo;
	}
}
