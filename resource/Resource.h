#ifndef RESOURCE_HEADER
#define RESOURCE_HEADER

namespace resource {

	class Resource
	{
	public:
		virtual bool Load() = 0;
		virtual void Release() = 0;

		virtual ~Resource() = default;
	};

}

#endif