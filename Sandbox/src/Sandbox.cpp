#include "Comet.h"
#include "CometEntrypoint.h"

class SandboxLayer : public comet::Layer {
public:
	virtual void onAttatch() override {
		quad_vertex_array = comet::VertexArray::create();
		quad_vertex_array->bind();


		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.8f, 0.4f, 1.0f, 0.0f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 0.3f, 0.1f, 0.7f, 1.0f, 1.0f, 0.0f, 
			 0.5f,  0.5f, 0.0f, 0.9f, 0.8f, 0.4f, 1.0f, 1.0f, 1.0f, 
			-0.5f,  0.5f, 0.0f, 0.9f, 0.8f, 0.4f, 1.0f, 0.0f, 1.0f
		};

		auto vertex_buffer = comet::VertexBuffer::create();
		vertex_buffer->bind();
		vertex_buffer->setData(sizeof(vertices), vertices, comet::BufferUsage::STATIC);
		vertex_buffer->setLayout({
			{ comet::BufferLayout::Type::FLOAT3, "a_position" }, 
			{ comet::BufferLayout::Type::FLOAT4, "a_color" },
			{ comet::BufferLayout::Type::FLOAT2, "a_texture_coords" }
		});
		quad_vertex_array->addVertexBuffer(vertex_buffer);


		uint32_t indices[] = {
			0, 1, 2, 0, 2, 3
		};

		auto index_buffer = comet::IndexBuffer::create();
		index_buffer->bind();
		index_buffer->setData(6, indices, comet::BufferUsage::STATIC);
		quad_vertex_array->setIndexBuffer(index_buffer);


		quad_shader = comet::Shader::createFromFile("basic_textured.vert.glsl", "basic_textured.frag.glsl");
		quad_shader->bind();


		water_texture = comet::Texture2D::create("water.png", true);
		water_texture->bind(0);
		quad_shader->setUniformInt("sampler", 0);
	}

	virtual void onDetatch() override {
		quad_vertex_array = comet::Ref<comet::VertexArray>(nullptr);
	}

	virtual void onUpdate(comet::Timestep dt) override {
		comet::RenderCommand::setClearColor(0.3f, 0.1f, 0.7f);
		comet::RenderCommand::clear();

		comet::Renderer::drawIndexed(quad_vertex_array, quad_shader);
	}

	virtual void onEvent(comet::Event& e) override {
		
	}
private:
	comet::Ref<comet::VertexArray> quad_vertex_array;
	comet::Ref<comet::Shader> quad_shader;
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
