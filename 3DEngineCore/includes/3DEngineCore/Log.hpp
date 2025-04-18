#pragma once
#include "spdlog/spdlog.h"

namespace Engine
{
#ifdef NDEBUG
#define LOG_INFO(...) 
#define LOG_WARN(...)
#define LOG_ERROR(...) 
#define LOG_CRIT(...)
#else // DEBUG
#define LOG_INFO(...)  spdlog::info(__VA_ARGS__)
#define LOG_WARN(...)  spdlog::error(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::warn(__VA_ARGS__)
#define LOG_CRIT(...)  spdlog::critical(__VA_ARGS__)
#endif 
}