#include "Texture.h"

namespace graph {


	Texture::Texture(GLenum target, GLenum interalFormat):_buffer_id(0),_internalFormat(interalFormat)
	{
		glGenTextures(1, &_buffer_id);
		_internalFormat = interalFormat;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &_buffer_id);
	}


}