#ifndef H_SERVICE_LOCATOR
#define H_SERVICE_LOCATOR

#include "ruru/RuRu.h"
#include "ruru/services/IService.h"

#include <typeindex>
#include <unordered_map>

NS_RURU_BEGIN

class ServiceLocator
{
	private:
		static std::unordered_map<ServiceType_t, IService*> m_Services;

	public:
		
		template<class T>
		static void AddService(T* service)
		{
			constexpr ServiceType_t type = T::Type;
	
			if (m_Services.find(type) != m_Services.end())
			{
				throw std::runtime_error("Service already exists");
			}

			m_Services[type] = service;
		}

		template<class T>
		static void RemoveService(T* service)
		{
			constexpr ServiceType_t type = T::Type;

			if (m_Services.find(type) == m_Services.end())
			{
				throw std::runtime_error("Service doesn't exist");
			}

			if (m_Services[type] != service)
			{	
				throw std::runtime_error("Service not in use");
			}

			m_Services.erase(type);
		}

		template<class T>
		static T* GetService()
		{
			constexpr ServiceType_t type = T::Type;
			
			if (m_Services.find(type) == m_Services.end())
			{
				throw std::runtime_error("Service doesn't exist");
			}

			return static_cast<T*>(m_Services[type]);
		}

		template<class T>
		static T* TryGetService()
		{
			constexpr ServiceType_t type = T::Type;
			
			if (m_Services.find(type) == m_Services.end())
			{
				return nullptr;
			}

			return static_cast<T*>(m_Services[type]);
		}	
};


NS_RURU_END
#endif
