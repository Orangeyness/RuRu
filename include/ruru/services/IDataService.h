#ifndef H_IDATA_SERVICE
#define H_IDATA_SERVICE

#include "ruru/RuRu.h"
#include "ruru/services/ServiceMixin.h"
#include "ruru/services/ServiceLocator.h"

NS_RURU_BEGIN

class IDataService : public ServiceMixin<IDataService>
{
	friend ServiceLocator;

	public:
		virtual int getScreenWidth() = 0;
		virtual int getScreenHeight() = 0;
		virtual uint64_t getGameFrameCount() = 0;
		virtual ~IDataService() { }
};

NS_RURU_END
#endif
