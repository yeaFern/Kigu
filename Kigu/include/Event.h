#pragma once

#include <queue>
#include <memory>
#include <functional>

enum class EventType
{
	WindowResize
};

class Event
{
public:
	const EventType Type;
protected:
	Event(EventType type)
		: Type(type)
	{
	}
};

class WindowResizeEvent : public Event
{
public:
	const int Width;
	const int Height;
public:
	WindowResizeEvent(int width, int height)
		: Event(EventType::WindowResize), Width(width), Height(height)
	{
	}
};

using EventPtr = std::shared_ptr<Event>;

class EventQueue
{
private:
	std::queue<EventPtr> m_Queue;
public:
	template<class T, class... Args>
	inline void Add(Args&&... args)
	{
		m_Queue.push(std::make_shared<T>(std::forward<Args>(args)...));
	}

	void Process(std::function<void(const Event&)> callback);
};
