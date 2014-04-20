#ifndef H_RURU_COMPONENT_TYPES
#define H_RURU_COMPONENT_TYPES

#include "ruru/RuRu.h"

#include <cstdlib>

NS_RURU_BEGIN

typedef size_t ComponentType_t;
typedef int ComponentHandle_t;

const ComponentHandle_t COMPONENT_NULL_HANDLE = -1;
const size_t COMPONENT_DEFAULT_ALLOCATION = 100;
const size_t COMPONENT_TYPE_COUNT = 100;

NS_RURU_END

#endif
