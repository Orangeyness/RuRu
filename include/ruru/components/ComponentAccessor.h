#ifndef H_RURU_COMPONENT_ACCESSOR
#define H_RURU_COMPONENT_ACCESSOR

#include "ruru/RuRu.h"
#include "ruru/entity/EntityManager.h"
#include "ruru/components/ComponentTypes.h"

NS_RURU_BEGIN

template<class T>
class ComponentAccessor
{
	friend EntityManager;
	
	private:
		ComponentHandle_t m_ComponentHandle;
		EntityHandle_t m_EntityHandle;
		EntityManager* m_EntityManager;

	protected:
		ComponentAccessor(EntityManager* em, EntityHandle_t entity, ComponentHandle_t handle)
			: m_ComponentHandle(handle), m_EntityHandle(entity), m_EntityManager(em) { }

	public:
		inline EntityHandle_t entity() const
		{
			return m_EntityHandle;
		}

		inline T* operator->() const
		{
			return m_EntityManager->getComponent<T>(m_ComponentHandle);
		}

		inline T* operator*() const
		{
			return m_EntityManager->getComponent<T>(m_ComponentHandle);
		}
};


NS_RURU_END

#endif
