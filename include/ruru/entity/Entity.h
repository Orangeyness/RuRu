#ifndef H_ENTITY
#define H_ENTITY

#include <array>

#include "ruru/RuRu.h"
#include "ruru/components/ComponentManager.h"
NS_RURU_BEGIN

typedef int EntityHandle_t;
class EntityManager;

class Entity
{
	friend EntityManager;

	private:
		EntityHandle_t m_EntityId;
		ComponentManager* m_ComponentLookUp;
		std::array<ComponentHandle_t, COMPONENT_TYPE_COUNT> m_Components; 
		int m_ComponentCount;

	protected:
		template<class T>
		inline ComponentHandle_t getComponentHandle()
		{
			return m_Components[T::Type];
		}

		inline void setComponent(ComponentType_t type, ComponentHandle_t handle)
		{
			if (hasComponent(type))
			{
				throw std::runtime_error("Cannot set component, type not unique");
			}

			m_ComponentCount += 1;
			m_Components[type] = handle;
		}
		
		inline void deleteComponent(ComponentType_t type)
		{
			if (!hasComponent(type))
			{
				throw std::runtime_error("Cannot delete component, type not set");
			}
		
			m_ComponentCount --;
			m_Components[type] = COMPONENT_NULL_HANDLE;
		}

	public:
		inline Entity(EntityHandle_t id, ComponentManager* componentManagerRef)
			: m_EntityId(id), m_ComponentLookUp(componentManagerRef), m_ComponentCount(0)
		{
			m_Components.fill(COMPONENT_NULL_HANDLE);
		}

		template<class T>
		inline T* getComponent() const
		{
			return m_ComponentLookUp->getComponent<T>(m_Components[T::Type]);
		}

		template<class T>
		inline ComponentHandle_t getComponentHandle() const
		{
			return m_Components[T::Type];
		}

		inline ComponentHandle_t getComponentHandle(ComponentType_t type) const
		{
			return m_Components[type];
		}

		template<class T>
		inline bool hasComponent() const
		{
			return m_Components[T::Type] != COMPONENT_NULL_HANDLE;
		}

		inline bool hasComponent(ComponentType_t type) const
		{
			return m_Components[type] != COMPONENT_NULL_HANDLE;
		}

		inline bool hasComponents() const
		{
			return m_ComponentCount > 0;
		}

		inline EntityHandle_t getEntityId() const
		{
			return m_EntityId;
		}

};

NS_RURU_END
#endif
