#include "Comet.h"
#include "CometEntrypoint.h"

class SandboxLayer : public comet::Layer {
public:
	virtual void onAttatch() override {
		
	}

	virtual void onDetatch() override {
		
	}

	virtual void onUpdate(comet::Timestep dt) override {
		CMT_INFO("Update (Frametime: {0})", dt);
	}

	virtual void onEvent(comet::Event& e) override {
		
	}
};


class SandboxApplication : public comet::Application {
public:
	SandboxApplication() {
		pushLayer(comet::makeRef<SandboxLayer>());
	}
};

comet::Application* comet::createApplication() {
	return new SandboxApplication();
}