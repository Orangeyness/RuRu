#ifndef H_ISERVICE
#define H_ISERVICE

#include "ruru/RuRu.h"
#include <cstdlib>

NS_RURU_BEGIN

const int SERVICE_IDENTIFIER_NOT_SET = 0;

typedef size_t ServiceType_t;

template<typename T>
class ServiceMixin
{
	friend class ServiceLocator;

	private:
		static ServiceType_t ServiceIdentifier;

};

template<typename T>
RuRu::ServiceType_t RuRu::ServiceMixin<T>::ServiceIdentifier = RuRu::SERVICE_IDENTIFIER_NOT_SET;

NS_RURU_END
#endif
