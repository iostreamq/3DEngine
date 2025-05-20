#pragma once
#include "EngineEventProcessing/EventsDispatcher.hpp"
#include <ResourceManagement/ResourceManagementSystem.hpp>
#include <System/FileSystem/DiskFileLoader.hpp>
#include <Parser/JSON/ParserComposite.hpp>
#include <memory>
#include <string>
#include "glad/glad.h"
#include <GLFW/glfw3.h>


namespace Engine {
   
    class ShaderProgram;

    class Window {
    public:
        Window(unsigned int width, unsigned int height, const char* title);
        int createWindow();
        void shutDown();
        void on_update();
        const unsigned int getWidth() const  { return m_data.m_width; }
        const unsigned int getHeight() const  { return m_data.m_height; }
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
        std::unique_ptr<IResourceManagementSystem> m_RMS_system;
        GLuint m_vao;
        std::shared_ptr<ShaderProgram> m_DefaultShaderProgram;
        std::unique_ptr<IFileLoader> m_fileLoader;
        std::unique_ptr<ParserComposite> m_parserMerging;
    };
}
