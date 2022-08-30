#include "Comet.h"
#include "CometEntrypoint.h"

class SandboxLayer : public comet::Layer {
public:
	virtual void onAttatch() override {
		camera = comet::OrthographicCamera::create({ 0.0f, 0.0f, 0.0f }, 2.0f, comet::Application::get()->getWindow()->getAspectRatio());
	}

	virtual void onDetatch() override {
		
	}

	virtual void onUpdate(comet::Timestep dt) override {
		comet::RenderCommand::setClearColor(0.3f, 0.1f, 0.7f);
		comet::RenderCommand::clear();

		comet::Renderer2D::beginScene(camera);
		comet::Renderer2D::drawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		comet::Renderer2D::endScene();
	}

	virtual void onEvent(comet::Event& e) override {
		
	}
private:
	comet::Ref<comet::OrthographicCamera> camera;
};


class SandboxApplication : public comet::Application {
public:
	SandboxApplication() {
		pushLayer(comet::createRef<SandboxLayer>());
	}
};


comet::Application* comet::createApplication() {
	return new SandboxApplication();
}
