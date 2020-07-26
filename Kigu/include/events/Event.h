#pragma once

namespace Kigu
{
	enum class EventType
	{
		WindowClose,
		WindowResize
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

	struct WindowResizeEvent : public Event
	{
		uint32_t Width;
		uint32_t Height;

		WindowResizeEvent(uint32_t width, uint32_t height)
			: Width(width), Height(height), Event(EventType::WindowResize)
		{
		}
	};
}
