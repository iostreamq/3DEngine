#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <functional>

namespace Engine
{
	class BaseEvent;

	class Window
	{
	public:
		using EventCallback = std::function<void(const BaseEvent& event)>;

		Window(unsigned int&& width, unsigned int&& height, const char* title);
		int createWindow();

		 void makeContext();
		 bool windowShouldClose();
		 void swapBuffers();
		 void shutDown();
		 void on_update();
		 void setEventCallback(EventCallback&& evCallback) {data.eventCallback = std::move(evCallback);}
	private:
		static bool is_GLFW_initialized;
		GLFWwindow* m_window;
		struct Data
		{
			unsigned int m_width;
			unsigned int m_height;
			std::string m_title;
			EventCallback eventCallback;
		};
		Data data;
	};
}