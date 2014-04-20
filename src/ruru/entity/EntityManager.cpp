#include "ruru/entity/EntityManager.h"
using namespace RuRu;

EntityManager::EntityManager() { }

EntityManager::EntityManager(size_t initialCapacity)
	: m_Entities(initialCapacity) { }

EntityHandle_t EntityManager::createEntity()
{
	return m_Entities.emplace(m_Entities.nextId(), &m_ComponentManager);
}

Entity* EntityManager::get(EntityHandle_t handle)
{
	return &m_Entities.get(handle);
}

Entity* EntityManager::tryGet(EntityHandle_t handle)
{
	return m_Entities.tryGet(handle);
}

void EntityManager::deleteEntity(EntityHandle_t handle)
{
	if (m_EntityDeletedSet.find(handle) != m_EntityDeletedSet.end())
		return;

	m_EntityDeletedSet.insert(handle);

	Entity* entity = &m_Entities.get(handle);

	if (entity->hasComponents())
	{
		for (size_t type = 0; type < COMPONENT_TYPE_COUNT; type++)
		{
			ComponentHandle_t c = entity->getComponentHandle(type);

			if (c == COMPONENT_NULL_HANDLE) continue;

			m_ComponentManager.deleteComponent(type, c);
		}
	}

	m_Entities.remove(handle);
}

bool EntityManager::exists(EntityHandle_t handle) const
{
	return m_Entities.has(handle);
}

ContiguousVector<Entity>::const_iterator EntityManager::begin() const
{
	return m_Entities.cbegin();
}

ContiguousVector<Entity>::const_iterator EntityManager::end() const
{
	return m_Entities.cend();
}

void EntityManager::deleteFlagEntity(EntityHandle_t handle)
{
	m_EntityCleanupList.push_front(handle);
}

void EntityManager::deleteFlaggedEntities()
{
	while(! m_EntityCleanupList.empty())
	{
		deleteEntity(m_EntityCleanupList.front());

		m_EntityCleanupList.pop_front();
	}
}
