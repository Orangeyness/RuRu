#ifndef H_IDATA_SERVICE
#define H_IDATA_SERVICE

#include "ruru/RuRu.h"
#include "ruru/services/IService.h"
#include "ruru/services/ServiceLocator.h"
#include "ruru/services/ServiceTypes.h"

NS_RURU_BEGIN

class IDataService : public IService
{
	friend ServiceLocator;

	protected:
		constexpr static const ServiceType_t Type = SERVICE_DATA_TYPE_ID;

	public:
		virtual int getScreenWidth() = 0;
		virtual int getScreenHeight() = 0;
		virtual uint64_t getGameFrameCount() = 0;
		virtual ~IDataService() { }
};

NS_RURU_END
#endif
