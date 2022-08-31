#include "Comet.h"
#include "CometEntrypoint.h"

class SandboxLayer : public comet::Layer {
public:
	virtual void onAttatch() override {
		camera_controller = comet::createRef<comet::OrthographicCameraController>(
			comet::OrthographicCamera::create({ 0.0f, 0.0f, 0.0f }, 10.0f, comet::Application::get()->getWindow()->getAspectRatio()), 
			5.0f, 1.0f);
		water_texture = comet::Texture2D::create("water.png", true);
	}

	virtual void onDetatch() override {
		
	}

	virtual void onUpdate(comet::Timestep dt) override {
		comet::RenderCommand::setClearColor(0.3f, 0.1f, 0.7f);
		comet::RenderCommand::clear();

		camera_controller->onUpdate(dt);

		comet::Renderer2D::beginScene(camera_controller->getCamera());
		comet::Renderer2D::drawQuad({ -5.0f, -5.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f });
		comet::Renderer2D::drawQuad({  5.0f, -5.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
		comet::Renderer2D::drawQuad({  5.0f,  5.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f });
		comet::Renderer2D::drawQuad({ -5.0f,  5.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });
		comet::Renderer2D::drawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, water_texture);
		comet::Renderer2D::endScene();
	}

	virtual void onEvent(comet::Event& e) override {
		camera_controller->onEvent(e);
	}
private:
	comet::Ref<comet::OrthographicCameraController> camera_controller;
	comet::Ref<comet::Texture2D> water_texture;
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
