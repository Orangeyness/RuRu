#ifndef H_COLLISION_SYSTEM
#define H_COLLISION_SYSTEM

#include "ruru/entities/EntityManager.h"
#include "ruru/services/ServiceLocator.h"
#include "ruru/systems/SystemMixin.h"

#include "example/components/CollisionComponent.h"

#include <forward_list>
#include <utility>

class CollisionSystem : public RuRu::PairWiseSystemMixin<CollisionSystem, CollisionComponent>
{
	private:
		std::forward_list<std::pair<RuRu::EntityHandle_t, RuRu::EntityHandle_t>> m_CollisionList;

	protected:
		void resolveCollision(RuRu::EntityManager& em, 
			const RuRu::ServiceLocator& sl, RuRu::Entity& entity, RuRu::Entity& collider);

	public:
		void runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl, 
			CollisionComponent& first, CollisionComponent& second);

		void after(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl);

		using RuRu::PairWiseSystemMixin<CollisionSystem, CollisionComponent>::run;
};


#endif
