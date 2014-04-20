#include "example/systems/CollisionSystem.h"

#include "ruru/services/ServiceLocator.h"
#include "ruru/events/EventService.h"

#include "example/components/DamageableComponent.h"
#include "example/components/DamageDealingComponent.h"
#include "example/events/EntityDestroyEvent.h"

void CollisionSystem::detectCollisions(
	RuRu::ComponentIteratorConst<CollisionComponent> begin, 
	RuRu::ComponentIteratorConst<CollisionComponent> end)
{
	for (auto iter = begin; iter != end; iter++)
	{
		for(auto iter2 = iter + 1; iter2 != end; iter2++)
		{
			if (iter->colliding(*iter2))
			{
				m_CollisionList.emplace_front(iter->entity(), iter2->entity());
			}
		}
	}
}

void CollisionSystem::resolveCollisions(RuRu::EntityManager& em)
{
	detectCollisions(	em.component_cbegin<CollisionComponent>(),	
						em.component_cend<CollisionComponent>());

	while(! m_CollisionList.empty())
	{
		std::pair<RuRu::EntityHandle_t, RuRu::EntityHandle_t> collision = m_CollisionList.front();
		
		RuRu::Entity* e1 = em.get(collision.first);
		RuRu::Entity* e2 = em.get(collision.second);

		resolveCollision(em, e1, e2);
		resolveCollision(em, e2, e1);

		m_CollisionList.pop_front();
	}
}

void CollisionSystem::resolveCollision(
	RuRu::EntityManager& em, 
	RuRu::Entity* entity, 
	RuRu::Entity* collider)
{
	if (entity->hasComponent<DamageableComponent>() && collider->hasComponent<DamageDealingComponent>())
	{
		DamageableComponent* damageTaking = entity->getComponent<DamageableComponent>();
		DamageDealingComponent* damageDealing = collider->getComponent<DamageDealingComponent>();

		if (damageDealing->team() != damageTaking->team())
		{
			damageTaking->addDamage(damageDealing->damage());

			if (! damageDealing->pierce())
			{
				RuRu::ServiceLocator::GetService<RuRu::EventService>()
					->addEvent<EntityDestroyEvent>(new EntityDestroyEvent(collider));
				
				em.deleteFlagEntity(collider->getEntityId());
			}

			if (! damageTaking->alive()) 
			{	
				RuRu::ServiceLocator::GetService<RuRu::EventService>()
					->addEvent<EntityDestroyEvent>(new EntityDestroyEvent(entity));

				em.deleteFlagEntity(entity->getEntityId());
			}
		}
	}
}
