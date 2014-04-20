#include "example/components/BuffableComponent.h"

BuffableComponent::BuffableComponent(RuRu::EntityHandle_t entityId)
	: m_Buffs(), m_EntityId(entityId) { }

BuffableComponent* BuffableComponent::addBuff(RuRu::EntityManager& em, IBuff* buff)
{
	BuffData& data = m_Buffs[buff->getBuffType()];

	if (data.Active)
	{
		data.Handle->unbind(em, m_EntityId);
	}

	data.Handle = buff;
	data.LifeTime = buff->getLifeTime();
	data.Active = true;

	data.Handle->bind(em, m_EntityId);

	return this;
}

void BuffableComponent::ageBuffs(RuRu::EntityManager& em)
{
	for (auto& buff : m_Buffs)
	{
		if (! buff.Active) continue;

		buff.LifeTime --;

		if (buff.LifeTime < 0)
		{
			buff.Handle->unbind(em, m_EntityId);
			buff.Active = false;
			buff.Handle = nullptr;
		}
	}
}
