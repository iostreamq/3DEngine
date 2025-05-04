#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include "3DEngineCore/Window.hpp"
#include "3DEngineCore/Log.hpp"
#include "3DEngineCore/Event.hpp"
#include "glad/glad.h"


bool Engine::Window::is_GLFW_initialized = false;
Engine::Window::Window(unsigned int&& width, unsigned int&& height, const char* title)
	:  m_window(nullptr)
    , data({ std::move(width), std::move(height), title })
{}

int Engine::Window::createWindow()
{
    LOG_INFO("Creating window {0} width size {1}x{2}", data.m_title, data.m_width, data.m_height);
    /* Initialize the library */
    if (!glfwInit())
    {
        LOG_CRIT("Can`t initialiaze GLFW");
        is_GLFW_initialized = false;
        return -1;
    }
    else { LOG_INFO("GLFW intiliazed"); is_GLFW_initialized = true; }
     
   m_window = glfwCreateWindow(data.m_width, data.m_height, data.m_title.c_str(), NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        return -1;
    }
        
    glfwSetWindowUserPointer(m_window, &data);
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window,int width, int height)
        {   
            auto& winData = *static_cast<Data*>(glfwGetWindowUserPointer(window));
            winData.m_height = height;
            winData.m_width = width;

            const EventWindowResized eventWindowResized(width, height);
            winData.eventCallback(eventWindowResized);
        });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            auto& winData = *static_cast<Data*>(glfwGetWindowUserPointer(window));
            const EventWindowClose eventWindowClose;
            winData.eventCallback(eventWindowClose);
        });
   
        makeContext();

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRIT("Failed to initializied GLAD");
            return 0;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext(); 
        ImGui_ImplOpenGL3_Init();

        glClearColor(0, 1, 1, 0);
        return 0;

}

void Engine::Window::makeContext()
{
	glfwMakeContextCurrent(m_window);
}

bool Engine::Window::windowShouldClose()
{
	if (glfwWindowShouldClose(m_window))
		return true;
	else
		return false;
}

void Engine::Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Engine::Window::shutDown()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Engine::Window::on_update()
{   
        glClear(GL_COLOR_BUFFER_BIT);

      
        ImGuiIO& io = ImGui::GetIO(); // получили handle
        io.DisplaySize.x = static_cast<float>(getWidth());
        io.DisplaySize.y = static_cast<float>(getHeight());
        ImGui_ImplOpenGL3_NewFrame();//начинаем новый фрейм для отрисовки где имгуи рисует
        ImGui::NewFrame();// кадр самого имгуи
        ImGui::ShowDemoWindow(); // отрисовывает демо окно чтобы увидеть возможности имгуи
        ImGui::Render();// создает данные
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());//рисует посредством опенгл

        swapBuffers();
        glfwPollEvents();
}
