#pragma once
#include <memory>
#include <vector>
#include "EngineEventProcessing/IEventsExecutor.hpp"
#include "EngineEventProcessing/WindowEventsManager.hpp"
#include "EngineEventProcessing/IEvent.hpp"
#include "3DEngineCore/Log.hpp"

class WindowEventsExecutor : public IEventsExecutor
{
public:
	virtual void execute(const IEvent& event) override
	{
		const std::function<void(const IEvent& event)> solution = m_eventsManager.getEventExecution(typeid(event));
		if (solution)
			solution(event);
		else LOG_CRIT("Solution didn`t find!");
	}

private:
	WindowEventsManager m_eventsManager;
};
