#ifndef TEXTURE2D_HEADER
#define TEXTURE2D_HEADER

#include "Texture.h"

namespace graph
{
	class Texture2D :public Texture
	{
	private:
		int _width;
		int _height;
	private:
		Texture2D(GLenum internalFormat) :Texture(GL_TEXTURE_2D, internalFormat) { _internalFormat = internalFormat; };

	public:
		static Texture2D * Create(GLenum internalFormat, GLenum filter = GL_LINEAR, GLenum wrap = GL_REPEAT);

		//������������洢�ռ䣬�Ҵ洢�ռ䲻�ɱ䡣
		void Storage(GLsizei levels,GLsizei width,GLsizei height);
		//������������洢�ռ䣬�洢�ռ�ɱ�
		void TexImage(GLint level, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * data);
		//��data�������滻��������е�һ������
		void TexSubImage(GLint level,GLint xoffset,GLint yoffset,GLsizei width,GLsizei height,GLenum format,GLenum type,const void * data);
		//�ӵ�ǰFBO�п���ĳ��������ݵ����������
		void TexImageFromFBO(GLint level,GLint x,GLint y,GLsizei width,GLsizei height);

		void TexParameter(GLenum para, GLenum value);

		//����ǰ�����filter����Ϊmipmap ģʽ
		void EnableMipMap();

		~Texture2D() { glDeleteTextures(1,&_buffer_id); };
	};
}

#endif