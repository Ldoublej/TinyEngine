
#include "Image2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace resource
{
	bool Image2D::Load()
	{

		if(_is_load)
			return false;
		unsigned char * data = stbi_load(_file_name.c_str(), &_width, &_height, &_channels, 0);
		if (data == nullptr || _width + _height == 0)
			return false;
		_data = data;
		_is_load = true;
		return true;
	}

	void Image2D::Release()
	{
		if(_is_load)
			stbi_image_free(_data);
	}

	unsigned char *Image2D::GetData()
	{
		return _data;
	}

	int Image2D::GetWidth() const
	{
		return _width;
	}

	int Image2D::GetHeight() const
	{
		return _height;
	}

	int Image2D::GetChannelCount() const
	{
		return _channels;
	}

	std::string Image2D::GetFileName() const
	{
		return _file_name;
	}

	GLenum Image2D::GetFormat() const
	{
		return _format;
	}

	GLenum Image2D::GetType() const
	{
		return _type;
	}

	bool Image2D::IsLoad() const
	{
		return _is_load;
	}

	Image2D::~Image2D()
	{
		if (_is_load)
			Release();
	}
}
