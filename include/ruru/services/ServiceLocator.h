#ifndef H_SERVICE_LOCATOR
#define H_SERVICE_LOCATOR

#include "ruru/RuRu.h"
#include "ruru/services/ServiceMixin.h"

#include <typeindex>
#include <unordered_map>

NS_RURU_BEGIN

class ServiceLocator
{
	private:
		ServiceLocator* m_Parent;
		mutable std::unordered_map<ServiceType_t, void*> m_Services;

	protected:
		static ServiceType_t NextId;

		template<class T>
		inline ServiceType_t GetServiceIdentifier() const
		{
			if (T::ServiceIdentifier == SERVICE_IDENTIFIER_NOT_SET)
				T::ServiceIdentifier = ServiceLocator::NextId;

			return T::ServiceIdentifier;
		}

	public:
		ServiceLocator() 
			: m_Parent(nullptr) { }

		ServiceLocator(ServiceLocator* parent)
			: m_Parent(parent) { }

		template<class T>
		void add(T* service)
		{
			ServiceType_t type = GetServiceIdentifier<T>();
	
			if (m_Services.find(type) != m_Services.end())
			{
				if (m_Parent == nullptr)
					throw std::runtime_error("Service already exists");

				m_Parent->add<T>(service);
			}

			m_Services[type] = static_cast<void*>(service);
		}

		template<class T>
		void remove()
		{
			ServiceType_t type = GetServiceIdentifier<T>();

			if (m_Services.find(type) == m_Services.end())
			{
				if (m_Parent == nullptr)
					throw std::runtime_error("Service doesn't exist");
			
				m_Parent->remove<T>();
			}

			m_Services.erase(type);
		}

		template<class T>
		void remove(T* service)
		{
			ServiceType_t type = GetServiceIdentifier<T>();

			if (m_Services.find(type) == m_Services.end())
			{
				if (m_Parent == nullptr)
					throw std::runtime_error("Service doesn't exist");
			
				m_Parent->remove<T>(service);
			}

			if (m_Services[type] != service)
				throw std::runtime_error("Service not in use");

			m_Services.erase(type);
		}

		template<class T>
		T* get() const
		{
			ServiceType_t type = GetServiceIdentifier<T>();
			
			if (m_Services.find(type) == m_Services.end())
			{
				if (m_Parent == nullptr)
					throw std::runtime_error("Service doesn't exist");
		
				m_Parent->get<T>();
			}

			return static_cast<T*>(m_Services.at(type));
		}

		template<class T>
		T* tryGet() const
		{
			ServiceType_t type = GetServiceIdentifier<T>();
			
			if (m_Services.find(type) == m_Services.end())
			{
				if (m_Parent == nullptr)
					return nullptr;

				m_Parent->tryGet<T>();
			}

			return static_cast<T*>(m_Services.at(type));
		}	
};


NS_RURU_END
#endif
