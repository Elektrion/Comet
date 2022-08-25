#include "cmt_pch.h"
#include "Comet/Core/Log.h"

namespace comet {

	namespace console_colors {

		std::ostream& none(std::ostream& os)      { return os; }
		std::ostream& clear_all(std::ostream& os) { os << "\33[0m"; return os; }

		std::ostream& text_white(std::ostream& os)      { os << "\33[38;2;255;255;255m"; return os; }
		std::ostream& text_light_gray(std::ostream& os) { os << "\33[38;2;191;191;191m"; return os; }
		std::ostream& text_gray(std::ostream& os)       { os << "\33[38;2;127;127;127m"; return os; }
		std::ostream& text_dark_gray(std::ostream& os)  { os << "\33[38;2;063;063;063m"; return os; }
		std::ostream& text_black(std::ostream& os)      { os << "\33[38;2;000;000;000m"; return os; }

		std::ostream& text_yellow(std::ostream& os)     { os << "\33[38;2;255;255;000m"; return os; }
		std::ostream& text_orange(std::ostream& os)     { os << "\33[38;2;255;127;000m"; return os; }
		std::ostream& text_red(std::ostream& os)        { os << "\33[38;2;255;000;000m"; return os; }
		std::ostream& text_magenta(std::ostream& os)    { os << "\33[38;2;255;000;255m"; return os; }
		std::ostream& text_purple(std::ostream& os)     { os << "\33[38;2;127;000;255m"; return os; }
		std::ostream& text_blue(std::ostream& os)       { os << "\33[38;2;000;000;255m"; return os; }
		std::ostream& text_cyan(std::ostream& os)       { os << "\33[38;2;000;255;255m"; return os; }
		std::ostream& text_green(std::ostream& os)      { os << "\33[38;2;000;255;000m"; return os; }

		std::ostream& text_faint_yellow(std::ostream& os)  { os << "\33[38;2;191;191;063m"; return os; }
		std::ostream& text_faint_orange(std::ostream& os)  { os << "\33[38;2;223;127;063m"; return os; }
		std::ostream& text_faint_red(std::ostream& os)     { os << "\33[38;2;127;000;000m"; return os; }
		std::ostream& text_faint_magenta(std::ostream& os) { os << "\33[38;2;191;063;191m"; return os; }
		std::ostream& text_faint_purple(std::ostream& os)  { os << "\33[38;2;127;063;223m"; return os; }
		std::ostream& text_faint_blue(std::ostream& os)    { os << "\33[38;2;000;000;127m"; return os; }
		std::ostream& text_faint_cyan(std::ostream& os)    { os << "\33[38;2;000;127;127m"; return os; }
		std::ostream& text_faint_green(std::ostream& os)   { os << "\33[38;2;000;127;000m"; return os; }

		std::ostream& background_white(std::ostream& os)      { os << "\33[48;2;255;255;255m"; return os; }
		std::ostream& background_light_gray(std::ostream& os) { os << "\33[48;2;191;191;191m"; return os; }
		std::ostream& background_gray(std::ostream& os)       { os << "\33[48;2;127;127;127m"; return os; }
		std::ostream& background_dark_gray(std::ostream& os)  { os << "\33[48;2;063;063;063m"; return os; }
		std::ostream& background_black(std::ostream& os)      { os << "\33[48;2;000;000;000m"; return os; }

		std::ostream& background_yellow(std::ostream& os)     { os << "\33[48;2;255;255;000m"; return os; }
		std::ostream& background_orange(std::ostream& os)     { os << "\33[48;2;255;127;000m"; return os; }
		std::ostream& background_red(std::ostream& os)        { os << "\33[48;2;255;000;000m"; return os; }
		std::ostream& background_magenta(std::ostream& os)    { os << "\33[48;2;255;000;255m"; return os; }
		std::ostream& background_purple(std::ostream& os)     { os << "\33[48;2;127;000;255m"; return os; }
		std::ostream& background_blue(std::ostream& os)       { os << "\33[48;2;000;000;255m"; return os; }
		std::ostream& background_cyan(std::ostream& os)       { os << "\33[48;2;000;255;255m"; return os; }
		std::ostream& background_green(std::ostream& os)      { os << "\33[48;2;000;255;000m"; return os; }

		std::ostream& background_faint_yellow(std::ostream& os)  { os << "\33[48;2;191;191;063m"; return os; }
		std::ostream& background_faint_orange(std::ostream& os)  { os << "\33[48;2;223;127;063m"; return os; }
		std::ostream& background_faint_red(std::ostream& os)     { os << "\33[48;2;127;000;000m"; return os; }
		std::ostream& background_faint_magenta(std::ostream& os) { os << "\33[48;2;191;063;191m"; return os; }
		std::ostream& background_faint_purple(std::ostream& os)  { os << "\33[48;2;127;063;223m"; return os; }
		std::ostream& background_faint_blue(std::ostream& os)    { os << "\33[48;2;000;000;127m"; return os; }
		std::ostream& background_faint_cyan(std::ostream& os)    { os << "\33[48;2;000;127;127m"; return os; }
		std::ostream& background_faint_green(std::ostream& os)   { os << "\33[48;2;000;127;000m"; return os; }

	}


	Logger::Logger(const std::string& name) : name(name) {}

	void Logger::push_message(Mode mode, const std::string& message, console_colors::console_color_t color) {
		switch(mode) {
		case Mode::MODE_TRACE:
			std::cout << console_colors::text_gray;
			break;
		case Mode::MODE_INFO:
			std::cout << console_colors::text_white;
			break;
		case Mode::MODE_WARN:
			std::cout << console_colors::text_yellow;
			break;
		case Mode::MODE_ERROR:
			std::cout << console_colors::text_red;
			break;
		case Mode::MODE_COLORED:
			std::cout << color;
			break;
		}

		time_t t = time(nullptr);
		tm tm{};
		localtime_r(&t, &tm);

		std::cout << "[" << (tm.tm_hour < 10 ? "0" : "") << tm.tm_hour << ":" << (tm.tm_min < 10 ? "0" : "") << tm.tm_min << ":" << (tm.tm_sec < 10 ? "0" : "") << tm.tm_sec << "]"
			<< "[" << name << "] " << message << console_colors::clear_all << std::endl;
	}

	Logger core_logger("Comet");
	Logger client_logger("App");

}
