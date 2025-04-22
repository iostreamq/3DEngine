#pragma once
#include"EngineEventProcessing/IPublisher.hpp"

template<typename T>
class EventsPublisher : public IPublisher
{
public:	
	enum class EWindowEvents
	{
		CloseWindow
		////////
	};

	void setPointer(std::unique_ptr<IPublisher> pPublisher);
	void addSubscriber(const std::shared_ptr<ISubscriber>& subscriber) override;
	void allClear() override;
	void checkReactions() override;
private:
	/*EWindowEvents() = default;*/
	EWindowEvents(const EWindowEvents&) = delete;
	EWindowEvents operator=(const EWindowEvents&) = delete;
	static std::unique_ptr<IPublisher> m_pEventsPublisher;
};