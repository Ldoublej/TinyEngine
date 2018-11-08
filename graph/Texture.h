#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <glad/glad.h>

namespace graph {

	class Texture
	{
	protected:
		GLuint _buffer_id;
		GLenum _buffer_type;
		GLenum _internalFormat;

	protected:
		Texture(GLenum target, GLenum interalFormat);


	public:
		GLuint GetBufferID()
		{
			return _buffer_id;
		}
		GLenum GetBufferType()
		{
			return _buffer_type;
		}
		GLenum GetInternalFormat()
		{
			return _internalFormat;
		}


		virtual ~Texture() ;
	};

}


#endif