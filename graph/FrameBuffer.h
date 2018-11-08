#ifndef FRAME_BUFFER_HEADER
#define FRAME_BUFFER_HEADER

#include <glad/glad.h>
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
		FrameBuffer(GLenum target);

	public:
		static FrameBuffer * Create(GLenum target);

		GLuint GetBufferID() const { return _buffer_id; }
		GLenum GetBufferType() const { return _framebuffer_type; }

		//fbo ��������
		void AddAttachment(RenderBufferInfo info);
		void AddAttachment(GLsizei width, GLsizei height, GLenum internalFormat, GLenum attachment);


		//fbo״̬���
		GLenum GetBufferStatus() ;
		void PrintFrameBufferStatus(GLenum  status) ;

		~FrameBuffer();
	};

}

#endif