#include "example/systems/CollisionSystem.h"

#include "ruru/services/ServiceLocator.h"
#include "ruru/events/EventService.h"

#include "example/components/DamageableComponent.h"
#include "example/components/DamageDealingComponent.h"
#include "example/components/BuffableComponent.h"
#include "example/components/BuffHolderComponent.h"
#include "example/components/RenderComponent.h"
#include "example/events/EntityDestroyEvent.h"

void CollisionSystem::runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl,
	CollisionComponent& first, CollisionComponent& second)
{
	if (first.colliding(second))
	{
		m_CollisionList.emplace_front(first.entity(), second.entity());	
	}
}


void CollisionSystem::after(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl)
{
	while(! m_CollisionList.empty())
	{
		std::pair<RuRu::EntityHandle_t, RuRu::EntityHandle_t> collision = m_CollisionList.front();
		
		RuRu::Entity& e1 = em.get(collision.first);
		RuRu::Entity& e2 = em.get(collision.second);

		resolveCollision(em, sl, e1, e2);
		resolveCollision(em, sl, e2, e1);

		m_CollisionList.pop_front();
	}
}

void CollisionSystem::resolveCollision(
	RuRu::EntityManager& em, 
	const RuRu::ServiceLocator& sl,
	RuRu::Entity& entity, 
	RuRu::Entity& collider)
{
	if (entity.hasComponent<DamageableComponent>() && collider.hasComponent<DamageDealingComponent>())
	{
		DamageableComponent& damageTaking = entity.getComponent<DamageableComponent>();
		DamageDealingComponent& damageDealing = collider.getComponent<DamageDealingComponent>();

		if (damageDealing.team() != damageTaking.team())
		{
			damageTaking.addDamage(damageDealing.damage());

			if (! damageDealing.pierce())
			{
				sl.get<RuRu::EventService>()
					->addEvent<EntityDestroyEvent>(new EntityDestroyEvent(collider));
				
				em.deleteFlagEntity(collider.getEntityId());
			}

			if (! damageTaking.alive()) 
			{	
				sl.get<RuRu::EventService>()
					->addEvent<EntityDestroyEvent>(new EntityDestroyEvent(entity));

				em.deleteFlagEntity(entity.getEntityId());
			}
			else
			{
				if (entity.hasComponent<RenderComponent>())
				{
					entity.getComponent<RenderComponent>().setFlash();
				}
			}
		}
	}

	if (entity.hasComponent<BuffableComponent>() && collider.hasComponent<BuffHolderComponent>())
	{
		BuffableComponent& buffTaker = entity.getComponent<BuffableComponent>();
		BuffHolderComponent& buffGiver = collider.getComponent<BuffHolderComponent>();

		buffTaker.addBuff(em, buffGiver.getBuff());

		if (entity.hasComponent<RenderComponent>())
		{
			entity.getComponent<RenderComponent>().setFlash(al_map_rgb(0, 0, 255));
		}

		sl.get<RuRu::EventService>()
			->addEvent<EntityDestroyEvent>(new EntityDestroyEvent(collider));

		em.deleteFlagEntity(collider.getEntityId());
	}
}
