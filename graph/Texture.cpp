#include "Texture.h"

namespace graph {


	Texture::Texture(GLenum target, GLenum interalFormat):_buffer_id(0),_internal_format(interalFormat)
	{
		glGenTextures(1, &_buffer_id);
		_internal_format = interalFormat;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &_buffer_id);
	}

	GLuint Texture::GetBufferID() const
	{
		return _buffer_id;
	}

	GLenum Texture::GetBufferType() const
	{
		return _buffer_type;
	}

	GLenum Texture::GetInternalFormat() const
	{
		return _internal_format;
	}


}