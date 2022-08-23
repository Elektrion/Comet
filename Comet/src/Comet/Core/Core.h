#pragma once

#include "Comet/Core/Log.h"

#if defined(CMT_PLATFORM_WINDOWS)
	#define CMT_DEBUG_BREAK __debugbreak()
#else
	#define CMT_DEBUG_BREAK
#endif

#if (defined(CMT_DEBUG) || defined(CMT_RELEASE))
	#define CMT_CORE_TRACE(format, ...)          comet::core_logger.trace(format, __VA_ARGS__)
	#define CMT_CORE_INFO(format, ...)           comet::core_logger.info(format, __VA_ARGS__)
	#define CMT_CORE_WARN(format, ...)           comet::core_logger.warn(format, __VA_ARGS__)
	#define CMT_CORE_ERROR(format, ...)          comet::core_logger.error(format, __VA_ARGS__)
	#define CMT_CORE_COLORED(color, format, ...) comet::core_logger.colored(comet::console_colors::color, format, __VA_ARGS__)
	
	#define CMT_TRACE(format, ...)               comet::client_logger.trace(format, __VA_ARGS__)
	#define CMT_INFO(format, ...)                comet::client_logger.info(format, __VA_ARGS__)
	#define CMT_WARN(format, ...)                comet::client_logger.warn(format, __VA_ARGS__)
	#define CMT_ERROR(format, ...)               comet::client_logger.error(format, __VA_ARGS__)
	#define CMT_COLORED(color, format, ...)      comet::core_logger.colored(comet::console_colors::color, format, __VA_ARGS__)
#else
	#define CMT_CORE_TRACE(format, ...)
	#define CMT_CORE_INFO(format, ...)
	#define CMT_CORE_WARN(format, ...)
	#define CMT_CORE_ERROR(format, ...)
	#define CMT_CORE_COLORED(color, format, ...)
	
	#define CMT_TRACE(format, ...)
	#define CMT_INFO(format, ...)
	#define CMT_WARN(format, ...)
	#define CMT_ERROR(format, ...)
	#define CMT_COLORED(color, format, ...)
#endif


#if defined(CMT_ENABLE_ASSERTS)
	#define CMT_CORE_ASSERT(x, format, ...) { if(!x) { CMT_CORE_ERROR(format, __VA_ARGS__); CMT_DEBUG_BREAK; } }
	#define CMT_ASSERT(x, format, ...)      { if(!x) { CMT_ERROR(format, __VA_ARGS__); CMT_DEBUG_BREAK; } }
#else
	#define CMT_CORE_ASSERT(x, format, ...)
	#define CMT_ASSERT(x, format, ...)
	#define CMT_ASSERT(x)
#endif