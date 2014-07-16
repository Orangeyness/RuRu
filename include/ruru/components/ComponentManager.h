#ifndef H_COMPONENT_MANAGER
#define H_COMPONENT_MANAGER

#include <array>

#include "ruru/RuRu.h"
#include "ruru/components/ComponentTypes.h"
#include "ruru/helpers/ContiguousVector.h"

NS_RURU_BEGIN

class ComponentManager
{
	friend class EntityManager;

	private:
		std::array<IContiguousVector*, COMPONENT_TYPE_COUNT> m_Components;

	protected:
		template<class T>
		ContiguousVector<T>* getTypedContainer()
		{
			if (m_Components.at(T::Type) == nullptr)
			{
				m_Components[T::Type] = new ContiguousVector<T>(T::InitialAllocation);
			}
			
			return static_cast<ContiguousVector<T>*>(m_Components[T::Type]);
		}

		inline IContiguousVector* getContainer(ComponentType_t type) const
		{
			if (m_Components.at(type) == nullptr)
			{
				throw std::runtime_error("Cannot get component container, no components of that type exist");
			}
			
			return m_Components[type];
		}
	
		template<class T, typename ...RemainingParams>
		ComponentHandle_t create(RemainingParams &&... args)
		{
			ContiguousVector<T>* typedContainer = getTypedContainer<T>();
			
			return typedContainer->emplace(std::forward<RemainingParams>(args)...);
		}

		template<class T>
		ComponentHandle_t create(T t)
		{
			ContiguousVector<T>* typedContainer = getTypedContainer<T>();
			
			return typedContainer->add(t);
		}

		void remove(ComponentType_t type, ComponentHandle_t handle)
		{
			IContiguousVector* container = getContainer(type);
			container->remove(handle);
		}

		ComponentManager()
		{
			m_Components.fill(nullptr);
		}
		
	public:
		~ComponentManager()
		{
			for (size_t i = 0; i < COMPONENT_TYPE_COUNT; i++)
			{
				if (m_Components[i] == nullptr) continue;

				delete m_Components[i];
			}
		}

		template<class T>
		T& get(ComponentHandle_t handle)
		{
			ContiguousVector<T>* typedContainer = getTypedContainer<T>();
			
			return typedContainer->get(handle);
		}

		template<class T>
		void remove(ComponentHandle_t handle)
		{
			ContiguousVector<T>* typedContainer = getTypedContainer<T>();
	
			typedContainer->remove(handle);
		}

		template<class T>
		inline typename ContiguousVector<T>::const_iterator cbegin() const { return static_cast<ContiguousVector<T>*>(getContainer(T::Type))->cbegin(); }

		template<class T>
		inline typename ContiguousVector<T>::const_iterator cend() const { return static_cast<ContiguousVector<T>*>(getContainer(T::Type))->cend();	}

		template<class T>
		inline typename ContiguousVector<T>::iterator begin() { return getTypedContainer<T>()->begin(); }

		template<class T>
		inline typename ContiguousVector<T>::iterator end() { return getTypedContainer<T>()->end(); }
};

NS_RURU_END
#endif
