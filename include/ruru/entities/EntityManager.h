#ifndef H_ENTITY_MANAGER
#define H_ENTITY_MANAGER

#include <forward_list>
#include <unordered_set>

#include "ruru/RuRu.h"
#include "ruru/entities/Entity.h"
#include "ruru/components/ComponentManager.h"
#include "ruru/helpers/ContiguousVector.h"
NS_RURU_BEGIN

class EntityManager
{
	private:
		ContiguousVector<Entity> m_Entities;
		std::forward_list<EntityHandle_t> m_EntityCleanupList;
		std::unordered_set<EntityHandle_t> m_EntityDeletedSet;
		ComponentManager m_ComponentManager;

	public:
		typedef ContiguousVector<Entity>::iterator iterator;
		typedef ContiguousVector<Entity>::const_iterator const_iterator;

		EntityManager() { }
		EntityManager(size_t initialCapacity)
			: m_Entities(initialCapacity) { }
		
		inline EntityHandle_t createEntity()
		{
			return m_Entities.emplace(m_Entities.nextId(), m_ComponentManager);
		}

		inline void deleteEntity(EntityHandle_t handle)
		{
			if (m_EntityDeletedSet.find(handle) != m_EntityDeletedSet.end())
				return;

			m_EntityDeletedSet.insert(handle);

			Entity& entity = m_Entities.get(handle);

			if (entity.hasComponents())
			{
				for (size_t type = 0; type < COMPONENT_TYPE_COUNT; type++)
				{
					ComponentHandle_t c = entity.getComponentHandle(type);

					if (c == COMPONENT_NULL_HANDLE) continue;

					m_ComponentManager.remove(type, c);
				}
			}

			m_Entities.remove(handle);
		}

		inline bool exists(EntityHandle_t handle) const
		{
			return m_Entities.has(handle);
		}

		inline void deleteFlagEntity(EntityHandle_t handle)
		{
			m_EntityCleanupList.push_front(handle);
		}

		inline void deleteFlaggedEntities()
		{
			while(! m_EntityCleanupList.empty())
			{
				deleteEntity(m_EntityCleanupList.front());

				m_EntityCleanupList.pop_front();
			}
		}

		inline Entity& get(EntityHandle_t handle)
		{
			return m_Entities.get(handle);
		}

		inline Entity* tryGet(EntityHandle_t handle)
		{
			return m_Entities.tryGet(handle);
		}

		inline iterator begin() { return m_Entities.begin(); }
		inline iterator end() { return m_Entities.end(); }

		inline const_iterator cbegin() const
		{
			return m_Entities.cbegin();
		}

		inline const_iterator cend() const
		{
			return m_Entities.cend();
		}

		inline ComponentManager& components()
		{
			return m_ComponentManager;	
		}

		template<class T, typename ...RemainingParams>
		T& addComponent(EntityHandle_t entityHandle, RemainingParams &&... args)
		{
			ComponentHandle_t componentHandle = m_ComponentManager.create<T>(std::forward<RemainingParams>(args)...);

			get(entityHandle).bindComponent<T>(componentHandle);

			T& rtn = m_ComponentManager.get<T>(componentHandle);
			rtn.bind(entityHandle, this);
				
			return rtn;
		}

		template<class T>
		T& addComponent(EntityHandle_t entityHandle, T t)
		{
			ComponentHandle_t componentHandle = m_ComponentManager.create<T>(std::move(t));

			get(entityHandle).bindComponent<T>(componentHandle);

			T& rtn = m_ComponentManager.get<T>(componentHandle);
			rtn.bind(entityHandle, this);
				
			return rtn;
		}

		template<class T>
		void deleteComponent(EntityHandle_t entityHandle)
		{
			ComponentHandle_t componentHandle = get(entityHandle).unbindComponent<T>(componentHandle);
			m_ComponentManager.remove<T>(componentHandle);
		}

};

NS_RURU_END
#endif
