#ifndef H_RURU_EVENT_TYPES
#define H_RURU_EVENT_TYPES

#include "ruru/RuRu.h"
#include <cstdlib>

NS_RURU_BEGIN

typedef size_t EventDelegateHandle_t;
typedef size_t EventType_t;

const int EVENT_TYPE_COUNT = 100;
const int EVENT_TYPE_UNKNOWN = 666;

NS_RURU_END

#include "ruru/events/Event.h"

#endif
