#include "VertexArray.h"

namespace graph {

	VertexArray::VertexArray(ElementBuffer * ebo):_ebo(ebo)
	{
		glGenVertexArrays(1, &_buffer_id);
		if (!ebo)
			return;
		_ebo = ebo;
	}

	VertexArray * VertexArray::Create(ElementBuffer * ebo)
	{

		auto * vao = new VertexArray(ebo);
		if (vao->GetBufferID() == 0)
			return nullptr;
		return vao;
	}

	void VertexArray::AddVertexBuffer(VertexBuffer * vbo)
	{
		if (vbo == nullptr || vbo->GetBufferID() == 0)
			return;
		_vbo_list.push_back(vbo);
	}



	VertexBuffer * VertexArray::GetVertexBuffer(int index)
	{
		size_t size = _vbo_list.size();
		if (index + 1 > size)
		{
			return nullptr;
		}
		return _vbo_list.at(size);
	}

	void VertexArray::ApplyVertexAttributes()
	{
		glBindVertexArray(_buffer_id);
		
		if (_ebo != nullptr)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo->GetBufferID());
		}

		for (auto vbo:_vbo_list)
		{
			std::vector<VBOAttribute>::size_type attCount = vbo->GetAttributeCount();

			for (int j = 0; j < attCount; ++j)
			{
				VBOAttribute att = vbo->GetAttributeAt(j);
				VBOAttribute::AttributeType attType;
				attType = att.attributeType;

				if (attType == VBOAttribute::AttributeType::SinglePrecisionType)//单精度
				{
					glBindBuffer(GL_ARRAY_BUFFER, vbo->GetBufferID());
					glEnableVertexAttribArray(att.index);
					glVertexAttribPointer(att.index, att.size, att.type, att.normalized, att.stride, att.pointer);
				}
				else if (attType == VBOAttribute::AttributeType::IntegerType)//整型
				{
					glBindBuffer(GL_ARRAY_BUFFER, vbo->GetBufferID());
					glEnableVertexAttribArray(att.index);
					glVertexAttribIPointer(att.index, att.size, att.type, att.stride, att.pointer);
				}
				else if (attType == VBOAttribute::AttributeType::DoublePrecisionType)//双精度
				{
					//...
				}

			}
			
		}
		glBindVertexArray(0);
	}

	void VertexArray::SetElementBuffer(ElementBuffer * ebo)
	{
		if (ebo == nullptr)
			return;
		_ebo = ebo;
		glBindVertexArray(_buffer_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo->GetBufferID());
		glBindVertexArray(0);
	}

	GLuint VertexArray::GetBufferID() const
	{
		return _buffer_id;
	}

	ElementBuffer *VertexArray::GetElementBuffer() const
	{
		return _ebo;
	}

	std::vector<graph::VertexBuffer *>::size_type VertexArray::GetVertexBufferCount() const
	{
		return _vbo_list.size();
	}


}