#ifndef SIMPLEOGL_RESOURCE_H
#define SIMPLEOGL_RESOURCE_H

namespace resource {

	class Resource
	{
	protected:
		bool _is_load = false;
	public:
		virtual bool Load() = 0;
		virtual void Release() = 0;

		virtual ~Resource() = default;
	};

}

#endif //SIMPLEOGL_RESOURCE_H