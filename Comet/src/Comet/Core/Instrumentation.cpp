#include "cmt_pch.h"
#include "Instrumentation.h"

#include <fstream>

namespace comet {

	std::unique_ptr<std::thread> Instrumentation::worker = nullptr;
	std::vector<Instrumentation::InstrumentationData> Instrumentation::worker_buffer{};
	std::vector<Instrumentation::InstrumentationData> Instrumentation::submition_buffer{};
	volatile bool Instrumentation::work_available = false;
	volatile bool Instrumentation::stop_worker = false;

	bool Instrumentation::begin(const std::string& filename) {
		if(worker) return false;

		worker_buffer.reserve(256);
		submition_buffer.reserve(256);

		worker = std::make_unique<std::thread>([&, filename]() {

			std::ofstream os(filename, std::ios::out);
			if(!os) return false;

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

			return true;
		});

		return true;
	}

	void Instrumentation::end() {
		while(work_available) ;
		submition_buffer.swap(worker_buffer);
		work_available = true;
		while(work_available) ;
		stop_worker = true;
		worker->join();

		worker = nullptr;
		worker_buffer.clear();
		submition_buffer.clear();
		work_available = false;
		stop_worker = false;
	}

	void Instrumentation::submitEvent(InstrumentationData data) {
		if(!worker) return;

		submition_buffer.push_back(data);

		if(!work_available) {
			submition_buffer.swap(worker_buffer);
			work_available = true;
		}
	}

}
