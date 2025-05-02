#pragma once
#include "EngineEventProcessing/EventsDispatcher.hpp"
#include <memory>
#include <string>
#include "glad/glad.h"
#include <GLFW/glfw3.h>


namespace Engine {
    class Window {
    public:
        Window(unsigned int width, unsigned int height, const char* title);
        int createWindow();
        void shutDown();
        void on_update();
         std::unique_ptr<IEventsDispatcher>& getWindowDispatcher() { return m_windowEventsDispatcher; }


    private:
        struct Data
        {
            unsigned int m_width;
            unsigned int m_height;
            std::string m_title;
        };
        Data m_data;
        static bool is_GLFW_initialized;
        GLFWwindow* m_window{ nullptr };
        std::unique_ptr<IEventsDispatcher> m_windowEventsDispatcher;
    };
}
