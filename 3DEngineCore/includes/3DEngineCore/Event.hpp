#pragma once
#include<array>
#include<functional>

namespace Engine
{
	enum class EventType
	{
		WindowClosed,
		WindowResized,
		WindowCursor,

		Amount
	};

	struct BaseEvent
	{
		virtual ~BaseEvent() = default;
		virtual const EventType getType() const = 0;
	};

	struct EventWindowResized : BaseEvent
	{
		EventWindowResized(unsigned int width, unsigned int height)
			: m_width(width)
			, m_height(height) 
		{}

		const EventType getType() const override { return type; }
		const unsigned int getWidth() const  { return m_width; }
		const unsigned int getHeight() const  { return m_height; }


		static const EventType type  = EventType::WindowResized;
	private:
		unsigned int m_width;
		unsigned int m_height;
	};

	struct EventWindowClose : BaseEvent
	{
		EventWindowClose() = default;
		const EventType getType() const override { return type; }
		static const EventType type = EventType::WindowClosed;
	};
	
	class EventsDispatcher
	{
	public:
		template<typename TEvent>
		void addListener(std::function<void(const TEvent&)> eventСallback)
		{
			const auto& baseCallback = [func = std::move(eventСallback)](const BaseEvent& event)
				{
					func(static_cast<const TEvent&>(event));
				};

			m_events[static_cast<size_t>(TEvent::type)] = std::move(baseCallback);
		}

		void dispatch(const BaseEvent& event)
		{
			m_events[static_cast<size_t>(event.getType())](event);
		}

	private:
		std::array<std::function<void(const BaseEvent& event)>, static_cast<size_t>(EventType::Amount)> m_events;
	};



}
