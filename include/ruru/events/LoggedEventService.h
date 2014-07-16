#ifndef H_RURU_LOGGED_EVENT_SERVICE
#define H_RURU_LOGGED_EVENT_SERVICE

#include "ruru/RuRu.h"
#include "ruru/events/EventService.h"

#include <iostream>

NS_RURU_BEGIN

class LoggedEventService : public EventService
{
	friend ServiceLocator;

	private:
		EventService m_Base;
		std::ostream& m_Output;

	public:
		LoggedEventService(std::ostream& output)
			: m_Base(), m_Output(output) { }
		
		virtual void processEvents()
		{
			if (m_Events.empty()) return;

			m_Output << "Processing Event Batch Begin" << std::endl;
			
			while(! m_Events.empty())
			{	
				auto eventAndType = m_Events.front();

				EventDelegateList list = m_EventDelegates[eventAndType.first];
				Event* event = eventAndType.second;
				m_Output << event->toString() << std::endl;

				for (auto eventDelegate : list)
				{
					eventDelegate.second(event);
				}

				delete event;
				m_Events.pop_front();
			}

			m_Output << "Processing Event Batch End" << std::endl;
		}
};


NS_RURU_END
#endif
