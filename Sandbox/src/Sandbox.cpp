#include "Comet.h"
#include "CometEntrypoint.h"

class SandboxApplication : public comet::Application {
public:
	SandboxApplication() {
		CMT_INFO("Creating sandbox application");
	}
};

comet::Application* comet::createApplication() {
	return new SandboxApplication();
}