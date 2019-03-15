#ifndef SIMPLEOGL_VERTEXBUFFER_H
#define SIMPLEOGL_VERTEXBUFFER_H

#include <GL/glew.h>
#include <vector>
#include "VertexBufferBase.h"

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
		GLboolean normalized;
		GLsizei stride;
		const void * pointer;
	};

	class VertexBuffer: public VertexBufferBase
	{
	private:
		std::vector<VBOAttribute> _attribute_list;

		/*------------------------------------------------------------------------*/

	public:
		static VertexBuffer * Create();
		void AddAttribute( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer,VBOAttribute::AttributeType attributeType = VBOAttribute::SinglePrecisionType);
		void AddAttribute(VBOAttribute * attributes, int count);
		VBOAttribute GetAttributeAt(std::vector<VBOAttribute>::size_type index) const;
		std::vector<VBOAttribute>::size_type GetAttributeCount() const;
		~VertexBuffer() override = default;

	private:
		VertexBuffer() :VertexBufferBase(GL_ARRAY_BUFFER) {}
	};

}

#endif //SIMPLEOGL_VERTEXBUFFER_H
