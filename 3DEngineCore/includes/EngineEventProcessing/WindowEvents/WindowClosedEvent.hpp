#pragma once
#include "EngineEventProcessing/IEvent.hpp"

class WindowClosedEvent : public IEvent
{
public:
	 const char* getName() override { return "WindowClosedEvent"; };
};