#pragma once
#include<functional>
#include<memory>

template<typename... Args>
class ISubscriber
{
public:
	ISubscriber() = default;
	ISubscriber(const ISubscriber&) = delete;
	ISubscriber operator=(const ISubscriber&) = delete;
	virtual void setReaction(std::function<void(Args...)>);
private:
	using subscriberReaction = std::function<void(Args...)>;
};