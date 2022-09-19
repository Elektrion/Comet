#pragma once

#include <string>
#include <vector>
#include <string_view>

#include "Comet/Core/Core.h"

namespace comet {

	enum class BufferUsage {
		STATIC, DYNAMIC
	};

	class BufferLayout {
	public:
		struct Type {
		public:
			inline Type(std::string_view name, uint32_t component_count, uint32_t byte_count) noexcept : name(name), component_count(component_count), byte_count(byte_count) {}

			inline uint32_t getComponentCount() const noexcept { return component_count; }
			inline uint32_t getByteCount() const noexcept { return byte_count; }

			inline bool operator<(const Type& rhs) const noexcept { return name < rhs.name; }
		private:
			std::string_view name;
			uint32_t component_count;
			uint32_t byte_count;
		};
		
		static inline Type TYPE_FLOAT{ "Float", 1, 4 };
		static inline Type TYPE_FLOAT2{ "Float2", 2, 8 };
		static inline Type TYPE_FLOAT3{ "Float3", 3, 12 };
		static inline Type TYPE_FLOAT4{ "Float4", 4, 16 };

		struct Element {
			Type type;
			std::string_view name;
		};
	public:
		inline BufferLayout() noexcept : elements{}, byte_count(0) {}
		inline BufferLayout(std::initializer_list<Element> elements) : elements(elements), byte_count(0) {
			for(const auto& element : elements)
				byte_count += element.type.getByteCount();
		}

		inline void push(Element element) {
			elements.push_back(element);
			byte_count += element.type.getByteCount();
		}

		inline uint32_t getByteCount() const noexcept { return byte_count; }

		inline std::vector<Element>::iterator begin() noexcept { return elements.begin(); }
		inline std::vector<Element>::const_iterator begin() const noexcept { return elements.begin(); }
		inline std::vector<Element>::iterator end() noexcept { return elements.end(); }
		inline std::vector<Element>::const_iterator end() const noexcept { return elements.end(); }
	private:
		std::vector<Element> elements;
		uint32_t byte_count;
	};


	class VertexBuffer {
	public:
		virtual inline ~VertexBuffer() noexcept = default;

		inline VertexBuffer(const VertexBuffer&) noexcept = delete;
		inline VertexBuffer(const VertexBuffer&&) noexcept = delete;
		inline VertexBuffer& operator=(const VertexBuffer&) noexcept = delete;
		inline VertexBuffer& operator=(const VertexBuffer&&) noexcept = delete;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual void setData(uint32_t size, void* data, BufferUsage usage) = 0;

		virtual void setLayout(const BufferLayout& layout) = 0;
	protected:
		inline VertexBuffer() noexcept = default;
	public:
		static Ref<VertexBuffer> create();
	};


	class IndexBuffer {
	public:
		virtual inline ~IndexBuffer() noexcept = default;

		inline IndexBuffer(const IndexBuffer&) noexcept = delete;
		inline IndexBuffer(const IndexBuffer&&) noexcept = delete;
		inline IndexBuffer& operator=(const IndexBuffer&) noexcept = delete;
		inline IndexBuffer& operator=(const IndexBuffer&&) noexcept = delete;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual uint32_t getCount() const noexcept = 0;

		virtual void setData(uint32_t count, void* data, BufferUsage usage) = 0;
	protected:
		inline IndexBuffer() noexcept = default;
	public:
		static Ref<IndexBuffer> create();
	};

}
