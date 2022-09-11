#include "cmt_pch.h"
#include "Instrumentation.h"

#include "Comet/Core/Core.h"

namespace comet {

	InstrumentationTimer::InstrumentationTimer(const std::string& name) : name(name) {
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::microseconds> ts = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
		Instrumentation::submitEvent({ name, 'B', ts.time_since_epoch().count(), 0, std::hash<std::thread::id>{}(std::this_thread::get_id()) });
	}

	InstrumentationTimer::~InstrumentationTimer() {
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::microseconds> ts = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
		Instrumentation::submitEvent({ name, 'E', ts.time_since_epoch().count(), 0, std::hash<std::thread::id>{}(std::this_thread::get_id()) });
	}

	std::unique_ptr<std::thread> Instrumentation::worker = nullptr;
	std::vector<Instrumentation::InstrumentationData> Instrumentation::worker_buffer{};
	std::vector<Instrumentation::InstrumentationData> Instrumentation::submition_buffer{};
	volatile bool Instrumentation::work_available = false;
	volatile bool Instrumentation::stop_worker = false;

	/*std::string Instrumentation::active_file = "";
	std::ofstream Instrumentation::os{};*/

	void Instrumentation::begin(const std::string& filename) {
		if(worker)
			return;

		worker_buffer.reserve(1024);
		submition_buffer.reserve(1024);

		worker = std::make_unique<std::thread>([&, filename]() {

			std::ofstream os(filename, std::ios::out);
			if(!os) {
				CMT_CORE_WARN("Could not output to file \"{0}\"", filename);
				return;
			}

			os << "[ \n";
			os.flush();

			while(!stop_worker) {
				if(work_available) {
					for(const auto& data : worker_buffer) {
						os << "{ " <<
							"\"name\": \"" << data.name << "\", " <<
							"\"ph\": \"" << data.ph << "\", " <<
							"\"ts\": " << data.ts << ", " <<
							"\"pid\": " << data.pid << ", " <<
							"\"tid\": " << data.tid << " }, \n";
					}
					os.flush();
					worker_buffer.clear();
					work_available = false;
				}
			}

			os.flush();
			os.close();

		});

		/*if(filename == "")
			return;
		if(active_file != "")
			end();
		active_file = filename;

		
		os.open(active_file, std::ios::out);
		if(!os) {
			CMT_CORE_WARN("Could not output to file \"{0}\"", filename);
			return;
		}
		os << "[ \n";
		os.flush();*/
	}

	void Instrumentation::end() {
		while(work_available) 
			;
		submition_buffer.swap(worker_buffer);
		work_available = true;
		while(work_available) 
			;
		stop_worker = true;
		worker->join();

		worker = nullptr;
		worker_buffer.clear();
		submition_buffer.clear();
		work_available = false;
		stop_worker = false;

		/*os.flush();
		os.close();
		active_file = "";*/
	}

	void Instrumentation::submitEvent(InstrumentationData data) {
		if(!worker)
			return;

		submition_buffer.push_back(data);

		if(!work_available) {
			submition_buffer.swap(worker_buffer);
			work_available = true;
		}

		/*os << "{ " <<
			"\"name\": \"" << data.name << "\", " <<
			"\"ph\": \"" << data.ph << "\", " <<
			"\"ts\": " << data.ts << ", " <<
			"\"pid\": " << data.pid << ", " <<
			"\"tid\": " << data.tid << " }, \n";*/
	}

}
