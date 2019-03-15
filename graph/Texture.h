#ifndef SIMPLEOGL_TEXTURE_H
#define SIMPLEOGL_TEXTURE_H

#include <GL/glew.h>

namespace graph {

	class Texture
	{
	protected:
		GLuint _buffer_id;
		GLenum _buffer_type;
		GLenum _internal_format;

	protected:
		Texture(GLenum target, GLenum interalFormat);


	public:
		GLuint GetBufferID() const;
		GLenum GetBufferType() const;
		GLenum GetInternalFormat() const;
		virtual ~Texture();
	};

}


#endif//SIMPLEOGL_TEXTURE_H