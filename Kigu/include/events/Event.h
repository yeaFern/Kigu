#pragma once

namespace Kigu
{
	enum class EventType
	{
		WindowClose
	};

	struct Event
	{
		const EventType Type;

		Event(EventType type)
			: Type(type)
		{
		}

		virtual ~Event() = default;
	};

	struct WindowCloseEvent : public Event
	{
		WindowCloseEvent()
			: Event(EventType::WindowClose)
		{
		}
	};
}
