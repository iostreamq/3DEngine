#pragma once
#include<memory>

class IEvent;

class IEventsExecutor
{
public:
	virtual ~IEventsExecutor() = default;
	virtual void execute(const IEvent& event) = 0;
};