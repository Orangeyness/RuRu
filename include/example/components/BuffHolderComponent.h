#ifndef H_BUFF_HOLDER_COMPONENT
#define H_BUFF_HOLDER_COMPONENT

#include "ruru/components/ComponentMixin.h"

#include "example/components/ComponentTypes.h"
#include "example/buffs/IBuff.h"

class BuffHolderComponent : public RuRu::ComponentMixin
{
	private:
		IBuff* m_Buff;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_BUFFHOLDER;
		constexpr static const size_t InitialAllocation = 20;
		
		BuffHolderComponent(IBuff* buff)
			: m_Buff(buff) { }

		IBuff* getBuff() { return m_Buff; }
};

#endif
