#include "3DEngineCore/Application.hpp"
#include "3DEngineCore/Log.hpp"
#include "glad/glad.h"
#include "spdlog/spdlog.h"
#include "3DEngineCore/Window.hpp"
namespace Engine
{
    Application::Application()
    { 
        LOG_INFO("Start Application!");
    }

    Application::~Application()
    {
        LOG_INFO("Destroy Application!");
    }

    unsigned int Application::start(unsigned int&& window_width, unsigned int&& window_height, const char* title)
    {
        m_window = std::make_unique<Window>(std::move(window_width), std::move(window_height), title);
        m_window->createWindow();
     


        while (true)
        {
            m_window->on_update();
            on_update();
        }
        m_window->shutDown();
        return 0;
    }
}
