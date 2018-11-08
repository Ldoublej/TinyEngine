#include "Texture2D.h"

namespace graph
{
	Texture2D * Texture2D::Create(GLenum internalFormat, GLenum filter , GLenum wrap)
	{
		Texture2D * tex = new Texture2D(internalFormat);
		if (tex->GetBufferID() == 0)
			return nullptr;

		glBindTexture(GL_TEXTURE_2D, tex->GetBufferID());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glBindTexture(GL_TEXTURE_2D, 0);
		return tex;
	}
	void Texture2D::Storage(GLsizei levels, GLsizei width, GLsizei height)
	{
		if (width==0 || height == 0)
			return;
		glBindTexture(GL_TEXTURE_2D, _buffer_id);
		glTexStorage2D(GL_TEXTURE_2D, levels,_internalFormat, width, height);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture2D::TexImage(GLint level, GLsizei width, GLsizei height,GLenum format,GLenum type, const void * data)
	{
		if (width == 0 || height == 0)
			return;
		glBindTexture(GL_TEXTURE_2D, _buffer_id);
		glTexImage2D(GL_TEXTURE_2D, level, _internalFormat, width, height, 0, format, type, data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture2D::TexSubImage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * data)
	{
		if ((width == 0 || height == 0)|| yoffset + xoffset < 0)
			return;
		glBindTexture(GL_TEXTURE_2D, _buffer_id);
		glTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, width, height, format, type, data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//
	void Texture2D::TexImageFromFBO(GLint level, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		if ((width == 0 || height == 0) || y + x < 0)
			return;
		glBindTexture(GL_TEXTURE_2D, _buffer_id);
		glCopyTexImage2D(GL_TEXTURE_2D, level, _internalFormat, x, y, width, height, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture2D::TexParameter(GLenum para, GLenum value)
	{
		glBindTexture(GL_TEXTURE_2D, _buffer_id);
		glTexParameteri(GL_TEXTURE_2D, para, value);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture2D::EnableMipMap()
	{
		glBindTexture(GL_TEXTURE_2D, _buffer_id);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}