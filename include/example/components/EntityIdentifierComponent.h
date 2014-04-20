#ifndef H_ENTITY_IDENTIFIER_COMPONENT
#define H_ENTITY_IDENTIFIER_COMPONENT

#include "example/components/ComponentTypes.h"

typedef size_t EntityTypeId_t;

class EntityIdentifierComponent
{
	private:
		EntityTypeId_t m_EntityType;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_ENTITY_IDENTIFIER;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;
		
		EntityIdentifierComponent(EntityTypeId_t type)
			: m_EntityType(type) { }


		inline EntityTypeId_t type() { return m_EntityType; }
};


#endif
