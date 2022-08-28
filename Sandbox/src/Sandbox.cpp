#include "Comet.h"
#include "CometEntrypoint.h"

class SandboxLayer : public comet::Layer {
public:
	virtual void onAttatch() override {
		quad_vertex_array = comet::VertexArray::create();
		quad_vertex_array->bind();


		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 
			 0.5f,  0.5f, 0.0f, 
			-0.5f,  0.5f, 0.0f
		};

		auto vertex_buffer = comet::VertexBuffer::create();
		vertex_buffer->bind();
		vertex_buffer->setData(sizeof(vertices), vertices, comet::BufferUsage::STATIC);
		vertex_buffer->setLayout({
			{ comet::BufferLayout::Type::FLOAT3, "a_position" }
		});
		quad_vertex_array->addVertexBuffer(vertex_buffer);


		uint32_t indices[] = {
			0, 1, 2, 0, 2, 3
		};

		auto index_buffer = comet::IndexBuffer::create();
		index_buffer->bind();
		index_buffer->setData(6, indices, comet::BufferUsage::STATIC);
		quad_vertex_array->setIndexBuffer(index_buffer);


		quad_shader = comet::Shader::create(R"(
			#version 410 core
			
			layout(location = 0) in vec3 a_position;
			
			void main() {
				gl_Position = vec4(a_position, 1.0f);
			}
		)", R"(
			#version 410 core
			
			out vec4 color;
			
			void main() {
				color = vec4(0.9f, 0.8f, 0.4f, 1.0f);
			}
		)");

		quad_shader->bind();
	}

	virtual void onDetatch() override {
		quad_vertex_array = comet::Ref<comet::VertexArray>(nullptr);
	}

	virtual void onUpdate(comet::Timestep dt) override {
		comet::RenderCommand::setClearColor(0.3f, 0.1f, 0.7f);
		comet::RenderCommand::clear();

		comet::Renderer::drawIndexed(quad_vertex_array);
	}

	virtual void onEvent(comet::Event& e) override {
		
	}
private:
	comet::Ref<comet::VertexArray> quad_vertex_array;
	comet::Ref<comet::Shader> quad_shader;
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
