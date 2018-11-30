#include "VertexArray.h"

namespace graph {

	VertexArray::VertexArray(GLenum primitiveType, ElementBuffer * ebo):_primitive_type(primitiveType),_ebo(nullptr)
	{
		glGenVertexArrays(1, &_buffer_id);
		if (!ebo)
			return;
		_ebo = ebo;
	}

	VertexArray * VertexArray::Create(GLenum primitiveType, ElementBuffer * ebo)
	{

		VertexArray * vao = new VertexArray(primitiveType,ebo);
		if (vao->GetBufferID() == 0)
			return nullptr;
		return vao;
	}

	void VertexArray::AddVertexBuffer(VertexBuffer * vbo)
	{
		if (vbo == nullptr && vbo->GetBufferID() == 0)
			return;
		_vbo_list.push_back(vbo);
	}



	VertexBuffer * VertexArray::GetVertexBuffer(int index)
	{
		int size = _vbo_list.size();
		if (index + 1 > size)
		{
			return nullptr;
		}
		return _vbo_list.at(index);
	}

	void VertexArray::ApplyVertexAttributes()
	{
		glBindVertexArray(_buffer_id);
		
		if (_ebo != nullptr)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo->GetBufferID());
		}

		int vboCount = _vbo_list.size();
		for (int i = 0; i < vboCount; ++i)
		{
			VertexBuffer * vbo = _vbo_list.at(i);
			int attCount = vbo->GetAttributeCount();

			for (int j = 0; j < attCount; ++j)
			{
				VBOAttribute att = vbo->GetAttributeAt(j);
				VBOAttribute::AttributeType attType;
				attType = att.attributeType;

				if (attType == VBOAttribute::AttributeType::SinglePrecisionType)//Ӧ�ø����Ͷ�������
				{
					glBindBuffer(GL_ARRAY_BUFFER, vbo->GetBufferID());
					glEnableVertexAttribArray(att.index);
					glVertexAttribPointer(att.index, att.size, att.type, att.normalized, att.stride, att.pointer);
				}
				else if (attType == VBOAttribute::AttributeType::IntegerType)//Ӧ�����Ͷ�������
				{
					glBindBuffer(GL_ARRAY_BUFFER, vbo->GetBufferID());
					glEnableVertexAttribArray(att.index);
					glVertexAttribIPointer(att.index, att.size, att.type, att.stride, att.pointer);
				}
				else if (attType == VBOAttribute::AttributeType::DoublePrecisionType)//�ݲ�ʵ��
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


	

}