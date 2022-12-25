#include "pch.h"
#include "log_manager.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "thsan/log.h"

namespace Thsan {



		/*
		spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

		s_coreLogger = spdlog::stdout_color_mt("THSAN");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("CLIENT");
		s_clientLogger->set_level(spdlog::level::trace);
		*/


	void LogManager::init()
	{
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%^---%L---%$] [thread %t] %v");

		std::vector<spdlog::sink_ptr> sinks{ console_sink };
		auto logger = std::make_shared<spdlog::logger>(CORE_DEFAULT_LOGGER_NAME, sinks.begin(), sinks.end());
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);

		auto logger_client = std::make_shared<spdlog::logger>(CLIENT_DEFAULT_LOGGER_NAME, sinks.begin(), sinks.end());
		logger_client->set_level(spdlog::level::trace);
		logger_client->flush_on(spdlog::level::trace);

		spdlog::register_logger(logger);
		spdlog::register_logger(logger_client);
	}

	void LogManager::close()
	{
		spdlog::shutdown();
	}

}