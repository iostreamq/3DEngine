#pragma once
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include "EngineEventProcessing/IEventsDispatcher.hpp"
#include "EngineEventProcessing/IEventsExecutor.hpp"
#include "EngineEventProcessing/IEvent.hpp"

class EventsDispatcher : public IEventsDispatcher {
public:

    EventsDispatcher(std::unique_ptr<IEventsExecutor>&& exe)  { m_executor = std::move(exe); }

    void addEvent(std::unique_ptr<IEvent>&& event) override {
        m_events.push_back(std::move(event));  
    }

    void callExecutor() override {
        for (auto& currentEvent : m_events) {
            m_executor->execute(*currentEvent);
        }
    }

    void clearEvents() override {
        m_events.clear();
    }


private:
    std::unique_ptr<IEventsExecutor> m_executor;
    std::vector<std::unique_ptr<IEvent>> m_events; 
};

