#ifndef H_ENTITY_DESTROY_EVENT
#define H_ENTITY_DESTROY_EVENT

#include "ruru/entity/Entity.h"
#include "example/EntitySpawner.h"
#include "example/events/EventTypes.h"
#include "example/components/EntityIdentifierComponent.h"

#include <sstream>

class EntityDestroyEvent : public RuRu::Event
{
	public:
		constexpr static const RuRu::EventType_t Type = ENTITY_DESTROY_EVENT;
		virtual RuRu::EventType_t getType() const { return Type; }	

		RuRu::EntityHandle_t entityId;
		EntityTypeId_t entityType;
		double x;
		double y;

		EntityDestroyEvent(RuRu::Entity* entity)
		{
			entityId = entity->getEntityId();
		
			if (entity->hasComponent<EntityIdentifierComponent>())
			{
				EntityIdentifierComponent* ident = entity->getComponent<EntityIdentifierComponent>();

				entityType = ident->type();
			}
			else
			{
				entityType = ENTITY_BASIC;
			}
		

			if (entity->hasComponent<PositionComponent>())
			{
				PositionComponent* pos = entity->getComponent<PositionComponent>();
				x = pos->x;
				y = pos->y;
			}
			else
			{
				x = -1;
				y = -1;
			}
		}
	
		virtual std::string toString() const
		{
			std::stringstream ss;
			ss << "Event [Type=EntityDestroyEvent";
			ss << ", entityId=" << entityId;
			ss << ", entityType=" << entityType;
			ss << ", at=(" << x << ", " << y << ")]";
			

			return ss.str();
		}
};

#endif
