#ifndef H_RURU_EVENT_SERVICE
#define H_RURU_EVENT_SERVICE

#include "ruru/RuRu.h"
#include "ruru/events/EventTypes.h"

#include "ruru/services/ServiceMixin.h"
#include "ruru/services/ServiceLocator.h"

#include <functional>
#include <forward_list>
#include <array>

NS_RURU_BEGIN

typedef std::function<void(const Event*)> EventDelegate;
typedef std::pair<EventDelegateHandle_t, EventDelegate> EventDelegateAndIdTuple;
typedef std::forward_list<EventDelegateAndIdTuple> EventDelegateList;
typedef std::pair<EventType_t, Event*> EventAndTypeTuple;

class EventService : public ServiceMixin<EventService>
{
	friend ServiceLocator;

	private:
		static EventDelegateHandle_t NextId;

	protected:
		std::array<EventDelegateList, EVENT_TYPE_COUNT> m_EventDelegates;
		std::forward_list<EventAndTypeTuple> m_Events;

	public:
		EventService()
			: m_EventDelegates() { }

		~EventService()
		{
			while(! m_Events.empty())
			{
				Event* event = m_Events.front().second;
				delete event;

				m_Events.pop_front();
			}
		}

		template<class T> EventDelegateHandle_t addEventDelegate(EventDelegate delegate)
		{
			EventDelegateHandle_t id = NextId++;
			EventDelegateList& list = m_EventDelegates[T::Type];

			list.emplace_front(id, delegate);

			return id;
		}

		template<class T> void removeEventDelegate(EventDelegateHandle_t id)
		{
			EventDelegateList& list = m_EventDelegates[T::Type];
		
			list.remove_if([id](EventDelegateAndIdTuple v) { return v.first == id; });
		}
	
		template<class T> void addEvent(T* event)
		{
			constexpr const EventType_t type = T::Type;

			m_Events.emplace_front(type, event);	
		}
	
		virtual void processEvents()
		{
			while(! m_Events.empty())
			{	
				auto eventAndType = m_Events.front();

				EventDelegateList list = m_EventDelegates[eventAndType.first];
				Event* event = eventAndType.second;

				for (auto eventDelegate : list)
				{
					eventDelegate.second(event);
				}

				delete event;
				m_Events.pop_front();
			}
		}
};


NS_RURU_END
#endif
