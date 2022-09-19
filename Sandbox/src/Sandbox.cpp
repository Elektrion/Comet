#include "Comet.h"
#include "CometEntrypoint.h"


constexpr int32_t background_size_half = 50;

class SandboxLayer : public comet::Layer {
public:
	virtual void onAttatch() override {
		camera_controller = comet::createRef<comet::OrthographicCameraController>(
			comet::OrthographicCamera::create({ 0.0f, 0.0f, 0.0f }, 10.0f, comet::Application::get()->getWindow()->getAspectRatio()), 
			5.0f, 1.0f);
		water_texture = comet::Texture2D::create("water.png", true);
		grass_01_texture = comet::Texture2D::create("grass_01.png", true);
		grass_02_texture = comet::Texture2D::create("grass_02.png", true);
		for(auto& tile : background)
			tile = comet::Math::randBool();
	}

	virtual void onDetatch() override {
		
	}

	virtual void onUpdate(comet::Timestep dt) override {
		comet::RenderCommand::setClearColor(0.3f, 0.1f, 0.7f);
		comet::RenderCommand::clear();

		camera_controller->onUpdate(dt);

		comet::Renderer2D::beginScene(camera_controller->getCamera());
		for(int32_t y = -background_size_half; y < background_size_half; y++)
			for(int32_t x = -background_size_half; x < background_size_half; x++)
				comet::Renderer2D::drawQuad({ x, y }, { 1.0f, 1.0f }, 
					background[(y + background_size_half) * background_size_half * 2 + (x + background_size_half)] ? grass_01_texture : grass_02_texture);

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
	comet::Ref<comet::Texture2D> grass_01_texture;
	comet::Ref<comet::Texture2D> grass_02_texture;
	std::array<bool, background_size_half * 2 * background_size_half * 2> background;
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
