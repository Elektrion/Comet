#pragma once

#include <string>
#include <thread>
#include <memory>
#include <chrono>

namespace comet {

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
		static bool begin(const std::string& filename);
		static void end();
		static void submitEvent(InstrumentationData data);
	private:
		static std::unique_ptr<std::thread> worker;
		static std::vector<InstrumentationData> worker_buffer;
		static std::vector<InstrumentationData> submition_buffer;
		static volatile bool work_available;
		static volatile bool stop_worker;
	};

	class InstrumentationTimer {
	public:
		inline InstrumentationTimer(const std::string& name) noexcept : name(name) {
			Instrumentation::submitEvent({ name, 'B', std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count(),
				0, std::hash<std::thread::id>{}(std::this_thread::get_id()) });
		}

		inline ~InstrumentationTimer() noexcept {
			Instrumentation::submitEvent({ name, 'E', std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count(),
				0, std::hash<std::thread::id>{}(std::this_thread::get_id()) });
		}
	private:
		std::string name;
	};

}
