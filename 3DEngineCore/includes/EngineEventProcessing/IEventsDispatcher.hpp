#pragma once
#include <functional>
#include <memory>

class IEvent;
class IEventsExecutor;

class IEventsDispatcher {
public:
	virtual void addEvent(std::unique_ptr<IEvent>&& event) = 0;
	virtual void callExecutor() = 0;
	virtual void clearEvents() = 0;
	virtual ~IEventsDispatcher() = default;
};