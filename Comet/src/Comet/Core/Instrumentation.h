#pragma once

#include <string>
#include <chrono>
#include <ostream>
#include <thread>
#include <memory>

namespace comet {

	class InstrumentationTimer {
	public:
		InstrumentationTimer(const std::string& name);
		~InstrumentationTimer();
	private:
		std::string name;
	};

	class Instrumentation {
	public:
		struct InstrumentationData {
			std::string name;
			char ph;
			int64_t ts;
			uint64_t pid;
			uint64_t tid;
		};
	public:
		static void begin(const std::string& filename);
		static void end();
		static void submitEvent(InstrumentationData data);
	private:
		static std::unique_ptr<std::thread> worker;
		static std::vector<InstrumentationData> worker_buffer;
		static std::vector<InstrumentationData> submition_buffer;
		static volatile bool work_available;
		static volatile bool stop_worker;



		static std::string active_file;
		static std::ofstream os;
	};

}
