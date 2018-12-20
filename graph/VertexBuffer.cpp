#include "VertexBuffer.h"

namespace graph {


	VertexBuffer * VertexBuffer::Create()
	{
		auto * vbo = new VertexBuffer();
		if (vbo->GetBufferID() == 0)
			return nullptr;
		return vbo;
	}

	void VertexBuffer::AddAttribute( GLuint index, GLint size, GLenum type,GLboolean normalized, GLsizei stride, const void * pointer, VBOAttribute::AttributeType attributeType)
	{
		VBOAttribute att = VBOAttribute();
		att.attributeType = attributeType;
		att.index = index;
		att.size = size;
		att.type = type;
		att.normalized = normalized;
		att.stride = stride;
		att.pointer = pointer;

		_attribute_list.push_back(att);
	}
	void VertexBuffer::AddAttribute(VBOAttribute * attributes, int count)
	{
		if ((!count) && (!attributes))
			return;

		for (int i = 0; i < count; ++i)
		{
			_attribute_list.push_back(attributes[i]);
		}
	}
}