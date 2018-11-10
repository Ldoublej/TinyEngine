#ifndef SIMPLEOGL_TEXTURERE2DRESOURCE_H
#define SIMPLEOGL_TEXTURERE2DRESOURCE_H

#include "Resource.h"
#include <string>

namespace resource 
{

	class Texture2DResource :public Resource
	{
	private:
		std::string _file_name;
		int _width;
		int _height;
		int _channels;
		unsigned char * _data;
	public:
		Texture2DResource(const char * fileName) :_file_name(fileName) {}
		bool Load() override;
		void Release() override;
		unsigned char * GetData(){return _data;}
		int GetWidth(){return _width;}
		int GetHeight(){return _height;}
		int GetChannelCount(){return _channels;}
		std::string GetFileName(){return _file_name;};
		bool IsLoad(){return _loaded;}

		~Texture2DResource()
		{
			if (_loaded)
				Release();
		}
	};
}

#endif //SIMPLEOGL_TEXTURERE2DRESOURCE_H