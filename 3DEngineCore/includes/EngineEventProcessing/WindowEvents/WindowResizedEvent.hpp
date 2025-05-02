#pragma once
#include "EngineEventProcessing/IEvent.hpp"
#include <functional>

class WindowResizedEvent : public IEvent
{
public:
	WindowResizedEvent(const unsigned int& width, const unsigned int& height):
		m_width(width)
	  , m_height(height)
	{}

	const char* getName() override { return "WindowResizedEvent"; };
	
	unsigned int getWidth()  const  { return m_width; }
	unsigned int getHeight() const { return m_height; }

private:	
	unsigned int m_width;
	unsigned int m_height;
};
