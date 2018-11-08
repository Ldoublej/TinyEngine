#ifndef TEXTURE_RESOURCE_HEADER
#define TEXTURE_RESOURCE_HEADER

#include "Resource.h"
#include <string>

namespace resource 
{

	class TextureResource :public Resource
	{
	private:
		std::string _file_name;
		int _width;
		int _height;
		int _channels;
		bool _loaded;
		unsigned char * _data;
	public:
		TextureResource(const char * fileName) :_file_name(fileName),_loaded(false) {}
		bool Load() override;
		void Release() override;
		unsigned char * GetData(){return _data;}
		int GetWidth(){return _width;}
		int GetHeight(){return _height;}
		int GetChannelCount(){return _channels;}
		bool IsLoad(){return _loaded;}

		~TextureResource()
		{
			if (_loaded)
				Release();
		}
	};
}

#endif