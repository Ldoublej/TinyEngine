#ifndef SIMPLEOGL_FRAMEBUFFER_H
#define SIMPLEOGL_FRAMEBUFFER_H

#include <GL/glew.h>
#include <vector>
#include <stdio.h>

namespace graph {

	struct RenderBufferInfo
	{
		GLsizei width;
		GLsizei height;
		GLenum attachment;
		GLenum internalFormat;
	};


	class FrameBuffer
	{
	private:
		GLuint _buffer_id;
		GLenum _framebuffer_type;
		std::vector<GLuint> _renderbuffers_id;
	private:
		explicit FrameBuffer(GLenum target);

	public:
		static FrameBuffer * Create(GLenum target);
		GLuint GetBufferID() const;
		GLenum GetBufferType() const;
		void AddAttachment(RenderBufferInfo info);
		void AddAttachment(GLsizei width, GLsizei height, GLenum internalFormat, GLenum attachment);
		GLenum GetBufferStatus() ;
		void PrintFrameBufferStatus(GLenum  status) ;

		~FrameBuffer();
	};

}

#endif  //SIMPLEOGL_FRAMEBUFFER_H