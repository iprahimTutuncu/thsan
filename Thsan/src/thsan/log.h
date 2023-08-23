#pragma once
#include "pch.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#define CORE_DEFAULT_LOGGER_NAME "THSAN"
#define CLIENT_DEFAULT_LOGGER_NAME "CLIENT"


#if defined(TS_PLATFORM_WINDOWS)
	#define TS_BREAK __debugbreak();
#else
	#define TS_BREAK _builtin_trap();
#endif

#ifdef TS_CONFIG_DEBUG
	#define TS_CORE_TRACE(...)	  if(spdlog::get(CORE_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CORE_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
	#define TS_CORE_INFO(...)	  if(spdlog::get(CORE_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CORE_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
	#define TS_CORE_WARN(...)	  if(spdlog::get(CORE_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CORE_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
	#define TS_CORE_ERROR(...)	  if(spdlog::get(CORE_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CORE_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
	#define TS_CORE_CRITICAL(...) if(spdlog::get(CORE_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CORE_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}

	#define TS_CLIENT_TRACE(...)	if(spdlog::get(CLIENT_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CLIENT_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
	#define TS_CLIENT_INFO(...)		if(spdlog::get(CLIENT_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CLIENT_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
	#define TS_CLIENT_WARN(...)		if(spdlog::get(CLIENT_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CLIENT_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
	#define TS_CLIENT_ERROR(...)	if(spdlog::get(CLIENT_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CLIENT_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
	#define TS_CLIENT_CRITICAL(...) if(spdlog::get(CLIENT_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CLIENT_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}

	#define TS_CORE_ASSERT(x, msg)  if ((x)) {} else {TS_CORE_CRITICAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", x, msg, __FILE__, __LINE__); TS_BREAK};
	#define TS_CLIEN_ASSERT(x, msg) if ((x)) {} else {TS_CLIENT_CRITICAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", x, msg, __FILE__, __LINE__); TS_BREAK};
#else
	#define TS_CORE_TRACE(...)    (void)0 
	#define TS_CORE_WARN(...)     (void)0 
	#define TS_CORE_ERROR(...)    (void)0 
	#define TS_CORE_INFO(...)     (void)0 
	#define TS_CORE_CRITICAL(...) (void)0 

	#define TS_CLIENT_TRACE(...)    (void)0
	#define TS_CLIENT_INFO(...)     (void)0
	#define TS_CLIENT_WARN(...)     (void)0
	#define TS_CLIENT_ERROR(...)    (void)0
	#define TS_CLIENT_CRITICAL(...) (void)0
	#define TS_CORE_ASSERT(x, msg)  if ((x)) {} else {TS_CORE_CRITICAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", x, msg, __FILE__, __LINE__);};
	#define TS_CLIEN_ASSERT(x, msg) if ((x)) {} else {TS_CLIENT_CRITICAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", x, msg, __FILE__, __LINE__);};
#endif