#pragma once

#include <memory>

#include "Comet/Core/Log.h"

#if defined(CMT_PLATFORM_WINDOWS)
	#define CMT_DEBUG_BREAK __debugbreak()
#else
	#define CMT_DEBUG_BREAK
#endif

#if (defined(CMT_DEBUG) || defined(CMT_RELEASE))
	#define CMT_CORE_TRACE(...)          comet::core_logger.trace(__VA_ARGS__)
	#define CMT_CORE_INFO(...)           comet::core_logger.info(__VA_ARGS__)
	#define CMT_CORE_WARN(...)           comet::core_logger.warn(__VA_ARGS__)
	#define CMT_CORE_ERROR(...)          comet::core_logger.error(__VA_ARGS__)
	#define CMT_CORE_COLORED(color, ...) comet::core_logger.colored(comet::console_colors::color, __VA_ARGS__)
	
	#define CMT_TRACE(...)               comet::client_logger.trace(__VA_ARGS__)
	#define CMT_INFO(...)                comet::client_logger.info(__VA_ARGS__)
	#define CMT_WARN(...)                comet::client_logger.warn(__VA_ARGS__)
	#define CMT_ERROR(...)               comet::client_logger.error(__VA_ARGS__)
	#define CMT_COLORED(color, ...)      comet::core_logger.colored(comet::console_colors::color, __VA_ARGS__)
#else
	#define CMT_CORE_TRACE(...)
	#define CMT_CORE_INFO(...)
	#define CMT_CORE_WARN(...)
	#define CMT_CORE_ERROR(...)
	#define CMT_CORE_COLORED(color, ...)
	
	#define CMT_TRACE(...)
	#define CMT_INFO(...)
	#define CMT_WARN(...)
	#define CMT_ERROR(...)
	#define CMT_COLORED(color, ...)
#endif


#if defined(CMT_ENABLE_ASSERTS)
	#define CMT_CORE_ASSERT(x, ...) { if(!(x)) { CMT_CORE_ERROR(__VA_ARGS__); CMT_DEBUG_BREAK; } }
	#define CMT_ASSERT(x, ...)      { if(!(x)) { CMT_ERROR(__VA_ARGS__); CMT_DEBUG_BREAK; } }
#else
	#define CMT_CORE_ASSERT(x, ...)
	#define CMT_ASSERT(x, ...)
#endif


namespace comet {

	template<typename T> using Ref = std::shared_ptr<T>;

	template<typename T, typename... Types> inline Ref<T> createRef(Types&&... args) {
		return std::make_shared<T>(std::forward<Types>(args)...);
	}

	template<typename T> using Scope = std::unique_ptr<T>;

	template<typename T, typename... Types> inline Scope<T> createScope(Types&&... args) {
		return std::make_unique<T>(std::forward<Types>(args)...);
	}

}
