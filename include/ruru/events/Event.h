#ifndef H_RURU_EVENT
#define H_RURU_EVENT

#include "ruru/RuRu.h"
#include "ruru/events/EventTypes.h"
#include <string>

NS_RURU_BEGIN

class Event
{
	public:
		template<class T> const T* get() const
		{
			return static_cast<const T*>(this);	
		}
			
		virtual EventType_t getType() const
		{ 
			return EVENT_TYPE_UNKNOWN; 
		}

		virtual std::string toString() const
		{
			return std::string("Event [Type=" + std::to_string(getType()) + "]");
		}
	
		virtual ~Event() { }
};

NS_RURU_END

#endif
