#ifndef SIMPLEOGL_IMAGE2D_H
#define SIMPLEOGL_IMAGE2D_H

#include "Resource.h"
#include "GL/glew.h"
#include <string>

namespace resource 
{

	class Image2D :public Resource
	{
	private:
		std::string _file_name;
		int _width;
		int _height;
		int _channels;
		unsigned char * _data;
		GLenum  _format;
		GLenum _type;
	public:
		Image2D(const char * fileName,GLenum format,GLenum type) :_file_name(fileName),_width(0),_height(0),_channels(0),_data(nullptr)
		,_format(format),_type(type){}

		bool Load() override;
		void Release() override;

		unsigned char * GetData();
		int GetWidth() const;
		int GetHeight() const;
		int GetChannelCount() const;
		std::string GetFileName() const;
		GLenum GetFormat() const;
		GLenum GetType() const;
		bool IsLoad() const;

		~Image2D() override;
	};
}

#endif //SIMPLEOGL_IMAGE2D_H