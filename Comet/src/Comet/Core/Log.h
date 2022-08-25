#pragma once

#include <string>
#include <sstream>

namespace comet {

	namespace console_colors {
		using console_color_t = std::ostream&(std::ostream&);

		console_color_t none;
		console_color_t clear_all;

		console_color_t text_white;
		console_color_t text_light_gray;
		console_color_t text_gray;
		console_color_t text_dark_gray;
		console_color_t text_black;

		console_color_t text_yellow;
		console_color_t text_orange;
		console_color_t text_red;
		console_color_t text_magenta;
		console_color_t text_purple;
		console_color_t text_blue;
		console_color_t text_cyan;
		console_color_t text_green;

		console_color_t text_faint_yellow;
		console_color_t text_faint_orange;
		console_color_t text_faint_red;
		console_color_t text_faint_magenta;
		console_color_t text_faint_purple;
		console_color_t text_faint_blue;
		console_color_t text_faint_cyan;
		console_color_t text_faint_green;

		console_color_t background_white;
		console_color_t background_light_gray;
		console_color_t background_gray;
		console_color_t background_dark_gray;
		console_color_t background_black;

		console_color_t background_yellow;
		console_color_t background_orange;
		console_color_t background_red;
		console_color_t background_magenta;
		console_color_t background_purple;
		console_color_t background_blue;
		console_color_t background_cyan;
		console_color_t background_green;

		console_color_t background_faint_yellow;
		console_color_t background_faint_orange;
		console_color_t background_faint_red;
		console_color_t background_faint_magenta;
		console_color_t background_faint_purple;
		console_color_t background_faint_blue;
		console_color_t background_faint_cyan;
		console_color_t background_faint_green;
	}


	class Logger {
	public:
		Logger(const std::string& name);

		template<typename... Types> constexpr inline void trace(const std::string& format, const Types&... args) {
			push_message(Mode::MODE_TRACE, process_message(0, format, args...));
		}
		template<typename... Types> constexpr inline void info(const std::string& format, const Types&... args) {
			push_message(Mode::MODE_INFO, process_message(0, format, args...));
		}
		template<typename... Types> constexpr inline void warn(const std::string& format, const Types&... args) {
			push_message(Mode::MODE_WARN, process_message(0, format, args...));
		}
		template<typename... Types> constexpr inline void error(const std::string& format, const Types&... args) {
			push_message(Mode::MODE_ERROR, process_message(0, format, args...));
		}
		template<typename... Types> constexpr inline void colored(console_colors::console_color_t color, const std::string& format, const Types&... args) {
			push_message(Mode::MODE_COLORED, process_message(0, format, args...), color);
		}
	private:
		enum class Mode {
			MODE_TRACE, MODE_INFO, MODE_WARN, MODE_ERROR, MODE_COLORED
		};

		template<typename T, typename... Types> inline std::string process_message(size_t arg_pos, const std::string& format, const T& arg, const Types&... args) {
			size_t pos = format.find_first_of('{');
			if(pos == std::string::npos)
				return process_message(arg_pos, format);

			uint32_t arg_index = 0;
			for(size_t i = pos + 1; i < format.size(); i++) {
				if(format[i] >= '0' && format[i] <= '9')
					arg_index = arg_index * 10 + uint32_t(format[i] - '0');
				else if(format[i] == '}') {
					if(arg_index == arg_pos) {
						std::string front = format;
						front.erase(pos);
						front.append((std::ostringstream() << arg).str());
						return front + process_message(arg_pos + 1, format.substr(i + 1), args...);

					}
					return process_message(arg_pos + 1, format, args...);
				}
				else {
					error("Ill-formed log format string: \"{0}\"\n\tunexpected character '{1}' at position {2}, expected a digit or closing bracket", format, format[i], i);
					return "[Log message was ill-formed, for more information see the above log message]";
				}
			}
			
			error("Ill-formed log format string: \"{0}\"\n\tmissing closing bracket at the end of the format string", format);
			return "[Log message was ill-formed, for more information see the above log message]";
		}

		inline std::string process_message(size_t arg_pos, const std::string& format) { return format; }

		void push_message(Mode mode, const std::string& message, console_colors::console_color_t color = console_colors::none);
	private:
		std::string name;
	};

	extern Logger core_logger;
	extern Logger client_logger;

}
