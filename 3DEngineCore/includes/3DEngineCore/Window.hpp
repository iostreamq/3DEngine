#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>

namespace Engine
{
	class Window
	{
	public:
		
		Window(unsigned int&& width, unsigned int&& height, const char* title);
		int createWindow();

		 void makeContext();
		 bool windowShouldClose();
		 void swapBuffers();
		 void shutDown();
		 void on_update();
	private:
		static bool is_GLFW_initialized;
		GLFWwindow* m_window;
		unsigned int m_width;
		unsigned int m_height;
		std::string m_title;
	};
}