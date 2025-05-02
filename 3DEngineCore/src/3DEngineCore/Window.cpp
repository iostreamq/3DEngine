#include "3DEngineCore/Window.hpp"
#include "3DEngineCore/Log.hpp"
#include "EngineEventProcessing/WindowEvents/WindowClosedEvent.hpp"
#include "EngineEventProcessing/WindowEvents/WindowResizedEvent.hpp"
#include "EngineEventProcessing/WindowEventsExecutor.hpp"
#include <iostream>

bool Engine::Window::is_GLFW_initialized = false;

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    auto windowObject = static_cast<Engine::Window*>(glfwGetWindowUserPointer(window));
    if (windowObject) 
    {
        windowObject
            ->getWindowDispatcher()
            ->addEvent(std::make_unique<WindowResizedEvent>(width, height)); // вопросы по функционалу если бы была функция не из интерфейса то что тогда как чо я же в кторе определил поинтер     
        
    } 
    
}

void windowCloseCallback(GLFWwindow* window)
{
    auto windowObject = static_cast<Engine::Window*>(glfwGetWindowUserPointer(window));
    if (windowObject) { 

        windowObject
            ->getWindowDispatcher()
            ->addEvent(std::make_unique<WindowClosedEvent>());
    }
}

Engine::Window::Window(unsigned int width, unsigned int height, const char* title)
    : m_data({width, height, title})
    , m_windowEventsDispatcher(std::make_unique<EventsDispatcher>(std::make_unique<WindowEventsExecutor>()))
{}

int Engine::Window::createWindow() {

    LOG_INFO("Creating window {0} width size {1}x{2}", m_data.m_title, m_data.m_width, m_data.m_height);
    
    if (!glfwInit()) {
        LOG_CRIT("Can't initialize GLFW");
        is_GLFW_initialized = false;
        return -1;
    }
    is_GLFW_initialized = true;
    
    m_window = glfwCreateWindow(m_data.m_width, m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        return -1;
    }
    
    glfwSetWindowUserPointer(m_window, this);
    glfwSetWindowCloseCallback(m_window, windowCloseCallback);
    glfwSetWindowSizeCallback(m_window, windowSizeCallback);

    glfwMakeContextCurrent(m_window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_CRIT("Failed to initialize GLAD");
        return -1;
    }

    glClearColor(0, 1, 1, 0);
    return 0;
}

void Engine::Window::shutDown() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Engine::Window::on_update() {

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    m_windowEventsDispatcher->callExecutor();
    m_windowEventsDispatcher->clearEvents();

}
