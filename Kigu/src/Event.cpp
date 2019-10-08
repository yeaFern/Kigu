#include "Event.h"

void EventQueue::Process(std::function<void(const Event&)> callback)
{
	while (!m_Queue.empty())
	{
		EventPtr e = m_Queue.front();
		callback(*e);
		m_Queue.pop();

	}
}
