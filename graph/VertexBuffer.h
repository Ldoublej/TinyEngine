#ifndef VERTEX_BUFFER_HEADER
#define VERTEX_BUFFER_HEADER

#include <glad/glad.h>
#include <vector>
#include "BufferData.h"

namespace graph {

	struct VBOAttribute
	{
		enum AttributeType
		{
			SinglePrecisionType,
			IntegerType,
			DoublePrecisionType,
		} attributeType;
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;  //���attributeType����ΪIntegerType,��ô�ò���������
		GLsizei stride;
		const void * pointer;
	};

	class VertexBuffer: public BufferData
	{
	private:
		std::vector<VBOAttribute> _attribute_list;

		/*------------------------------------------------------------------------*/
	private:
		VertexBuffer() :BufferData(GL_ARRAY_BUFFER) {}

	public:
		static VertexBuffer * Create();

		//vbo�������Բ���
		void AddAttribute( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer,VBOAttribute::AttributeType attributeType = VBOAttribute::SinglePrecisionType);
		void AddAttribute(VBOAttribute * attributes, int count);
		VBOAttribute GetAttributeByIndex(int vaoIndex) = delete;
		VBOAttribute GetAttributeAt(int index) { return _attribute_list.at(index); };
		int GetAttributeCount() { return _attribute_list.size(); };

		~VertexBuffer() = default;
	};

}

#endif
