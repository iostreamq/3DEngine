#pragma once
#include "EngineEventProcessing/ISubscriber.hpp"

template<typename... Args>
class EventsSubscriber : public ISubscriber
{
public:
	void setReaction(std::function<void(Args...)>) override;
private:
	using subscriberReaction = std::function<void(Args...)>;
};