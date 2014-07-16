#ifndef H_RURU_COMPONENT_MIXIN
#define H_RURU_COMPONENT_MIXIN

#include "ruru/RuRu.h"
#include "ruru/entities/EntityManager.h"
#include "ruru/components/ComponentTypes.h"

NS_RURU_BEGIN

class ComponentMixin
{
	friend EntityManager;

	private:
		EntityManager* m_EntityManager;
		EntityHandle_t m_EntityHandle;

		inline void bind(EntityHandle_t entityHandle, EntityManager* entityManager)
		{
			m_EntityHandle = entityHandle;
			m_EntityManager = entityManager;
		}

	protected:
		ComponentMixin()
			: m_EntityManager(nullptr), m_EntityHandle(-1) { }

	public:
		template<class T>
		inline T& getSiblingComponent() const
		{
			return m_EntityManager->get(m_EntityHandle).getComponent<T>();
		}

		template<class T>
		inline bool hasSiblingComponent() const
		{
			return m_EntityManager->get(m_EntityHandle).hasComponent<T>();
		}

		inline EntityHandle_t entity() const
		{
			return m_EntityHandle;
		}
};


NS_RURU_END
#endif
