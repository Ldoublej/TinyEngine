#ifndef TINYENGINE_RESOURCE_H
#define TINYENGINE_RESOURCE_H

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