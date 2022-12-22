#pragma once

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

namespace Thsan {
	class THSAN_API Log 
	{
	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger;  }
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;

	};
};

#define TS_CORE_TRACE(...) ::Thsan::Log::getCoreLogger()->trace(__VA_ARGS__)
#define TS_CORE_INFO(...)  ::Thsan::Log::getCoreLogger()->info(__VA_ARGS__)
#define TS_CORE_WARN(...)  ::Thsan::Log::getCoreLogger()->warn(__VA_ARGS__)
#define TS_CORE_ERROR(...) ::Thsan::Log::getCoreLogger()->error(__VA_ARGS__)
#define TS_CORE_CRITICAL(...) ::Thsan::Log::getCoreLogger()->critical(__VA_ARGS__)

#define TS_CLIENT_TRACE(...) ::Thsan::Log::getClientLogger()->trace(__VA_ARGS__)
#define TS_CLIENT_INFO(...)  ::Thsan::Log::getClientLogger()->info(__VA_ARGS__)
#define TS_CLIENT_WARN(...)  ::Thsan::Log::getClientLogger()->warn(__VA_ARGS__)
#define TS_CLIENT_ERROR(...) ::Thsan::Log::getClientLogger()->error(__VA_ARGS__)
#define TS_CLIENT_CRITICAL(...) ::Thsan::Log::getClientLogger()->critical(__VA_ARGS__)