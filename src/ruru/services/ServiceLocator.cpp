#include "ruru/services/ServiceLocator.h"
using namespace RuRu;

std::unordered_map<ServiceType_t, IService*> ServiceLocator::m_Services;
