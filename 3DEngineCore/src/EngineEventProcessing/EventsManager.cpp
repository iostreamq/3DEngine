#pragma once
#include "EngineEventProcessing/EventsManager.hpp"
#include "EngineEventProcessing/WindowEvents/WindowResizedEvent.hpp"
#include "EngineEventProcessing/WindowEvents/WindowClosedEvent.hpp"
#include "GLFW/glfw3.h"
#include "EngineEventProcessing/IEvent.hpp" 
#include "3DEngineCore/Log.hpp"

WindowEventsManager::WindowEventsManager()
{
    m_executions[typeid(WindowResizedEvent)] = [](const IEvent& event) {
        const auto& resizeEvent = static_cast<const WindowResizedEvent&>(event);
        LOG_INFO("Resized to {}x{}", resizeEvent.getWidth(), resizeEvent.getHeight());
        };  

    m_executions[typeid(WindowClosedEvent)] = [](const IEvent& event) {
             LOG_INFO("Window closed!");
             glfwTerminate(); 
        };
}

const std::function<void(const IEvent& event)> WindowEventsManager::getEventExecution(const type_info& eventName)
{
    const auto& currentExecution = m_executions.find(eventName);
    if (currentExecution != m_executions.end())
    {
        return currentExecution->second;
    }
}   
