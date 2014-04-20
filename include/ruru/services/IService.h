#ifndef H_ISERVICE
#define H_ISERVICE

#include "ruru/RuRu.h"
#include <cstdlib>

NS_RURU_BEGIN

typedef size_t ServiceType_t;

class IService 
{
	public:
		virtual ~IService() { }
};


NS_RURU_END
#endif
