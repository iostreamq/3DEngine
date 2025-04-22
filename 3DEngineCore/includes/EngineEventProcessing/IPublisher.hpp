#pragma once
#include "EngineEventProcessing/ISubscriber.hpp"
#include <map>
#include <memory>

template<typename T>
class IPublisher
{
public:
	 virtual void addSubscriber(const std::shared_ptr<ISubscriber>& subscriber) = 0;
	 virtual void allClear() = 0;
	 virtual void checkReactions() = 0;
private:
	using reactions_map = std::map <T, std::shared_ptr<ISubscriber>>;
	reactions_map m_ReactionsMap;
};