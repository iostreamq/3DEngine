#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include "3DEngineCore/Window.hpp"
#include "3DEngineCore/Log.hpp"
#include "EngineEventProcessing/WindowEvents/WindowClosedEvent.hpp"
#include "EngineEventProcessing/WindowEvents/WindowResizedEvent.hpp"
#include "EngineEventProcessing/WindowEventsExecutor.hpp"
#include <Renderer/Shaders/ShaderProgram.hpp>
#include <iostream>


bool Engine::Window::is_GLFW_initialized = false;
class ShaderResourceManager;

GLfloat point[] = {
 0.0f, 0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 1.0f
};

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
    , m_RMS_system(std::make_unique<ResourceManagementSystem>())
    , m_vao(0)
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

    const std::shared_ptr<ShaderResourceManager>& ptr = m_RMS_system->getNecessaryRM<ShaderResourceManager>();
    ptr->init("D:/3DEngine/3DEngineCore/res/shaders/");
    m_DefaultShaderProgram = ptr->loadShaderProgram("DefaultShaderProgram", "VertexShader.txt", "FragmentShader.txt");

    m_vao = 0;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    GLuint points_vbo;
    glGenBuffers(1, &points_vbo); // отличие от glCreateBuffers
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint colors_vbo;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init();
    glClearColor(0, 1, 1, 0);
    return 0;
}

void Engine::Window::shutDown() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Engine::Window::on_update() {

    glClear(GL_COLOR_BUFFER_BIT);
    
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = getWidth();
    io.DisplaySize.y = getHeight();

    glBindVertexArray(m_vao);
    m_DefaultShaderProgram->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    glfwSwapBuffers(m_window);
    glfwPollEvents();
    m_windowEventsDispatcher->callExecutor();
    m_windowEventsDispatcher->clearEvents();

}
