#ifndef H_ENTITY_MANAGER
#define H_ENTITY_MANAGER

#include <forward_list>
#include <unordered_set>

#include "ruru/RuRu.h"
#include "ruru/entity/Entity.h"
#include "ruru/components/ComponentManager.h"
#include "ruru/helpers/ContiguousVector.h"
NS_RURU_BEGIN

template<class T> class ComponentAccessor;

template<class T>
using ComponentIterator = typename ContiguousVector<T>::iterator;

template<class T>
using ComponentIteratorConst = typename ContiguousVector<T>::const_iterator;

class EntityManager
{
	private:
		ContiguousVector<Entity> m_Entities;
		std::forward_list<EntityHandle_t> m_EntityCleanupList;
		std::unordered_set<EntityHandle_t> m_EntityDeletedSet;
		ComponentManager m_ComponentManager;

	public:
		EntityManager();
		EntityManager(size_t initialCapacity);
		
		EntityHandle_t createEntity();
		void deleteEntity(EntityHandle_t handle);
		bool exists(EntityHandle_t handle) const;
		void deleteFlagEntity(EntityHandle_t handle);
		void deleteFlaggedEntities();

		Entity* get(EntityHandle_t handle);
		Entity* tryGet(EntityHandle_t handle);

		ContiguousVector<Entity>::const_iterator begin() const;
		ContiguousVector<Entity>::const_iterator end() const;	

		template<class T>
		inline typename ContiguousVector<T>::const_iterator component_cbegin() const { return m_ComponentManager.component_cbegin<T>(); }

		template<class T>
		inline typename ContiguousVector<T>::const_iterator component_cend() const { return m_ComponentManager.component_cend<T>(); }

		template<class T>
		inline typename ContiguousVector<T>::iterator component_begin() { return m_ComponentManager.component_begin<T>(); }

		template<class T>
		inline typename ContiguousVector<T>::iterator component_end() { return m_ComponentManager.component_end<T>(); }

		template<class T, typename ...RemainingParams>
		T* addComponent(EntityHandle_t entityHandle, RemainingParams &&... args)
		{
			ComponentHandle_t componentHandle = m_ComponentManager.createComponent<T>(std::forward<RemainingParams>(args)...);

			get(entityHandle)->setComponent(T::Type, componentHandle);

			return m_ComponentManager.getComponent<T>(componentHandle);
		}

		template<class T>
		T* addComponent(EntityHandle_t entityHandle, T t)
		{
			ComponentHandle_t componentHandle = m_ComponentManager.createComponent<T>(std::move(t));

			get(entityHandle)->setComponent(T::Type, componentHandle);

			return m_ComponentManager.getComponent<T>(componentHandle);
		}

		template<class T>
		void deleteComponent(EntityHandle_t entityHandle)
		{
			Entity* entity = get(entityHandle);

			ComponentHandle_t componentHandle = entity->getComponentHandle(T::Type);
			m_ComponentManager.deleteComponent<T>(componentHandle);

			entity->deleteComponent(T::Type);
		}

		template<class T>
		inline T* getComponent(ComponentHandle_t componentHandle)
		{
			return m_ComponentManager.getComponent<T>(componentHandle);
		}

		template<class T>
		inline ComponentAccessor<T> getComponentAccessor(EntityHandle_t entityId)
		{
			Entity* e = get(entityId);
			
			if (! e->hasComponent<T>())
			{
				throw std::runtime_error("Cannot create accessor, entity doesn't have component");
			}
		
			return ComponentAccessor<T>(this, entityId, e->getComponentHandle<T>()); 
		}
};

NS_RURU_END
#endif
