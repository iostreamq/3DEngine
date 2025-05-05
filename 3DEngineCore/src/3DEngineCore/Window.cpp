#include "3DEngineCore/Window.hpp"
#include "3DEngineCore/Log.hpp"
#include "3DEngineCore/Event.hpp"
#include "glad/glad.h"
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>



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

    const char* vertex_shader =   
        "#version 460\n"
        "layout(location = 0) in vec3 vertexCoords;"
        "layout(location = 1) in vec3 vertexColor;"
        "out vec3 frag_color;"
        "void main()"
        "{"
          "frag_color = vertexColor;"
          "gl_Position = vec4(vertexCoords,1.0);"
        "}";
   

    const char* fragment_shader =
        "#version 460\n"
        "in vec3 frag_color;"
        "out vec4 color;"
        "void main() {"
        "color = vec4(frag_color, 1.0);"
        "}";
    

    GLint idProgram = 0;
    GLuint vao = 0;
bool Engine::Window::is_GLFW_initialized = false;
Engine::Window::Window(unsigned int&& width, unsigned int&& height, const char* title)
	:  m_window(nullptr)
    , data({ std::move(width), std::move(height), title })
{
  /*  glViewport(0, 0, getWidth(), getHeight());*/
}

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
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);

        GLint idVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(idVertex, 1, &vertex_shader, nullptr);
        glCompileShader(idVertex);

        GLint idFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(idFragment, 1, &fragment_shader, nullptr);
        glCompileShader(idFragment);

        idProgram = glCreateProgram();
        glAttachShader(idProgram, idVertex);
        glAttachShader(idProgram, idFragment);
        glLinkProgram(idProgram);

        glDeleteShader(idVertex);
        glDeleteShader(idFragment);

        vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

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
        glClearColor(m_backGroundColor[0], m_backGroundColor[1], m_backGroundColor[2], m_backGroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glUseProgram(idProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);
      
        ImGuiIO& io = ImGui::GetIO(); // получили handle
        io.DisplaySize.x = static_cast<float>(getWidth());
        io.DisplaySize.y = static_cast<float>(getHeight());
        ImGui_ImplOpenGL3_NewFrame();//начинаем новый фрейм для отрисовки где имгуи рисует
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();// кадр самого имгуи
        ImGui::ShowDemoWindow(); // отрисовывает демо окно чтобы увидеть возможности имгуи
        
        ImGui::Begin("BackGround Color Window");
        ImGui::ColorEdit4("BackGround Color", m_backGroundColor);
        ImGui::End();

      

        ImGui::Render();// создает данные
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());//рисует посредством опенгл
        

        swapBuffers();
        glfwPollEvents();
}
