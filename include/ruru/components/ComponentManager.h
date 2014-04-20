#ifndef H_COMPONENT_MANAGER
#define H_COMPONENT_MANAGER

#include <array>

#include "ruru/RuRu.h"
#include "ruru/components/ComponentTypes.h"
#include "ruru/helpers/ContiguousVector.h"

NS_RURU_BEGIN

class ComponentManager
{
	private:
		std::array<IContiguousVector*, COMPONENT_TYPE_COUNT> m_Components;

	public:
		ComponentManager()
		{
			m_Components.fill(nullptr);
		}
		
		~ComponentManager()
		{
			for (size_t i = 0; i < COMPONENT_TYPE_COUNT; i++)
			{
				if (m_Components[i] == nullptr) continue;

				delete m_Components[i];
			}
		}

		template<class T>
		ContiguousVector<T>* getTypedContainer()
		{
			if (m_Components.at(T::Type) == nullptr)
			{
				m_Components[T::Type] = new ContiguousVector<T>(T::InitialAllocation);
			}
			
			return static_cast<ContiguousVector<T>*>(m_Components[T::Type]);
		}

		IContiguousVector* getContainer(ComponentType_t type) const
		{
			if (m_Components.at(type) == nullptr)
			{
				throw std::runtime_error("Cannot get component container, not components of that type exist");
			}
			
			return m_Components[type];
		}
	
		template<class T, typename ...RemainingParams>
		ComponentHandle_t createComponent(RemainingParams &&... args)
		{
			ContiguousVector<T>* typedContainer = getTypedContainer<T>();
			
			return typedContainer->emplace(std::forward<RemainingParams>(args)...);
		}

		template<class T>
		ComponentHandle_t createComponent(T t)
		{
			ContiguousVector<T>* typedContainer = getTypedContainer<T>();
			
			return typedContainer->add(t);
		}

		template<class T>
		T* getComponent(ComponentHandle_t handle)
		{
			ContiguousVector<T>* typedContainer = getTypedContainer<T>();
			
			return &typedContainer->get(handle);
		}

		template<class T>
		void deleteComponent(ComponentHandle_t handle)
		{
			ContiguousVector<T>* typedContainer = getTypedContainer<T>();
	
			typedContainer->remove(handle);
		}

		void deleteComponent(ComponentType_t type, ComponentHandle_t handle)
		{
			IContiguousVector* container = getContainer(type);
			container->remove(handle);
		}

		template<class T>
		inline typename ContiguousVector<T>::const_iterator component_cbegin() const { return static_cast<ContiguousVector<T>*>(getContainer(T::Type))->cbegin(); }

		template<class T>
		inline typename ContiguousVector<T>::const_iterator component_cend() const { return static_cast<ContiguousVector<T>*>(getContainer(T::Type))->cend();	}

		template<class T>
		inline typename ContiguousVector<T>::iterator component_begin() const { return static_cast<ContiguousVector<T>*>(getContainer(T::Type))->begin(); }

		template<class T>
		inline typename ContiguousVector<T>::iterator component_end() const { return static_cast<ContiguousVector<T>*>(getContainer(T::Type))->end();	}
};

NS_RURU_END
#endif
