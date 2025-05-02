#pragma once
#include<memory>
#include"3DEngineCore/Event.hpp"

namespace Engine{
	class Window;

	class Application
	{
	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator = (const Application&) = delete;
		Application& operator = (Application&&) = delete;
	  
		virtual unsigned int start(unsigned int&& window_width, unsigned int&& window_height, const char* title);
	
		virtual void  on_update() {};
	  
	private:
		std::unique_ptr<Window> m_window; //// без юника не робэ
		EventsDispatcher m_eventDispatcher;
	};
}