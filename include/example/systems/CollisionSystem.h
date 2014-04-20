#ifndef H_COLLISION_SYSTEM
#define H_COLLISION_SYSTEM

#include "ruru/entity/EntityManager.h"

#include "example/components/CollisionComponent.h"

#include <forward_list>
#include <utility>

class CollisionSystem
{

	protected:
		std::forward_list<std::pair<RuRu::EntityHandle_t, RuRu::EntityHandle_t>> m_CollisionList;

		void detectCollisions(RuRu::ComponentIteratorConst<CollisionComponent> begin, RuRu::ComponentIteratorConst<CollisionComponent> end);
	public:
		void resolveCollisions(RuRu::EntityManager& em);
		void resolveCollision(RuRu::EntityManager& em, RuRu::Entity* entity, RuRu::Entity* collider);

};


#endif
