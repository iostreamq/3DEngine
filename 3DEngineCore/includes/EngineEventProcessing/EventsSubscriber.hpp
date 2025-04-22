#pragma once
#include "EngineEventProcessing/ISubscriber.hpp"

template<typename... Args>
class EventsSubscriber : public ISubscriber
{
public:
	void setReaction(std::function<void(Args...)>) override;
private:
	using SubscriberCallback = std::function<void(Args...)>;
	SubscriberCallback subscriberReaction;
};