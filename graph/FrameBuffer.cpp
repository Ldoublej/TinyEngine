#include "FrameBuffer.h"

namespace graph{



	FrameBuffer::FrameBuffer(GLenum target):_buffer_id(0),_framebuffer_type(target)
	{
		glGenFramebuffers(1,&_buffer_id);
	}

	FrameBuffer * FrameBuffer::Create(GLenum target)
	{
		auto * fbo = new FrameBuffer(target);
		if (fbo->GetBufferID() == 0)
			return nullptr;
		return fbo;
	}

	void FrameBuffer::AddAttachment(RenderBufferInfo info)
	{

		glBindFramebuffer(_framebuffer_type, _buffer_id);

		GLuint renderBuffer = 0;
		glGenRenderbuffers(1, &renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, info.internalFormat, info.width, info.height);
		glFramebufferRenderbuffer(_framebuffer_type, info.attachment, GL_RENDERBUFFER, renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(_framebuffer_type,0);
	}
	void FrameBuffer::AddAttachment(GLsizei width, GLsizei height, GLenum internalFormat, GLenum attachment)
	{
		RenderBufferInfo info = RenderBufferInfo();
		info.width = width;
		info.height = height;
		info.internalFormat = internalFormat;
		info.attachment = attachment;
		AddAttachment(info);
	}
	void FrameBuffer::AddAttachment(Texture2D *texture, GLenum attachment)
	{
		glBindFramebuffer(_framebuffer_type, _buffer_id);

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetBufferID(), 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(_framebuffer_type, 0);
	}
	GLenum FrameBuffer::CheckStatus() const
	{
		glBindFramebuffer(_framebuffer_type, _buffer_id);

		GLenum status = glCheckFramebufferStatus(_framebuffer_type);
		

		glBindFramebuffer(_framebuffer_type, 0);
		return status;
	}

	void FrameBuffer::PrintFrameBufferStatus(GLenum  status) 
	{
		switch (status)
		{
		case GL_FRAMEBUFFER_COMPLETE:
			printf("GL_FRAMEBUFFER_COMPLETE\n");
			break;
		case GL_FRAMEBUFFER_UNDEFINED:
			printf("GL_FRAMEBUFFER_UNDEFINED\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			printf("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			printf("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			printf("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			printf("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n");
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			printf("GL_FRAMEBUFFER_UNSUPPORTED\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			printf("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n");
			break;
		default:
			printf("unknown\n");
			break;
		}
	}

	FrameBuffer::~FrameBuffer()
	{
		std::vector<GLuint>::size_type renderBufferCount = _renderbuffers_id.size();
		for(auto i : _renderbuffers_id)
        {
            glDeleteRenderbuffers(1, &i);
        }
		glDeleteFramebuffers(1, &_buffer_id);
	}

	GLenum FrameBuffer::GetBufferType() const
	{
		return _framebuffer_type;
	}

	GLuint FrameBuffer::GetBufferID() const
	{
		return _buffer_id;
	}



}
