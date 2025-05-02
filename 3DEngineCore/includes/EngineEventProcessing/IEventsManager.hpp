#pragma once
#include <functional>

class IEvent;

class IEventManager
{
public:
	virtual ~IEventManager() = default;
	virtual  const std::function<void(const IEvent& event)> getEventExecution(const type_info& eventName) = 0;
};