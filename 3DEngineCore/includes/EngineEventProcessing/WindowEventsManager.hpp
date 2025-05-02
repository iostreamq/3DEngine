#pragma once
#include <map>
#include <typeindex>
#include "EngineEventProcessing/IEventsManager.hpp"

class WindowEventsManager : public IEventManager
{
public:
	WindowEventsManager();
	const std::function<void(const IEvent& event)> getEventExecution(const type_info& eventName) override;

private:
	std::unordered_map<std::type_index, std::function<void(const IEvent& event)>> m_executions;
};