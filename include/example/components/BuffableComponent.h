#ifndef H_BUFFABLE_COMPONENT
#define H_BUFFABLE_COMPONENT

#include "example/components/ComponentTypes.h"
#include "example/buffs/IBuff.h"

#include <array>

const int BUFF_SLOTS = 10;

struct BuffData
{
	BuffData()
	{
		Active = false;
		LifeTime = 0;
		Handle = nullptr;
	}

	bool Active;
	int LifeTime;
	IBuff* Handle;
};

class BuffableComponent
{
	private:
		std::array<BuffData, BUFF_SLOTS> m_Buffs;
		RuRu::EntityHandle_t m_EntityId;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_BUFFABLE;
		constexpr static const size_t InitialAllocation = 1;
		
		BuffableComponent(RuRu::EntityHandle_t entityId);
		BuffableComponent* addBuff(RuRu::EntityManager& em, IBuff* buff);

		void ageBuffs(RuRu::EntityManager& em);
};

#endif
