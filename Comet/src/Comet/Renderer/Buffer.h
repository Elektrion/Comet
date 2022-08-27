#pragma once

#include <string>

#include "Comet/Core/Core.h"

namespace comet {

	enum class BufferUsage {
		STATIC, DYNAMIC
	};

	class BufferLayout {
	public:
		struct Type {
		public:
			static Type FLOAT;
			static Type FLOAT2;
			static Type FLOAT3;
			static Type FLOAT4;
		public:
			inline uint32_t getComponentCount() const { return component_count; }
			inline uint32_t getByteCount() const { return byte_count; }

			inline bool operator<(const Type& rhs) const { return name < rhs.name; }
		private:
			inline Type(const std::string& name, uint32_t component_count, uint32_t byte_count) : name(name), component_count(component_count), byte_count(byte_count) {}
		private:
			std::string name;
			uint32_t component_count;
			uint32_t byte_count;
		};

		struct Element {
			Type type;
			std::string name;
		};
	public:
		inline BufferLayout() : elements{}, byte_count(0) {}
		inline BufferLayout(std::initializer_list<Element> elements) : elements(elements), byte_count(0) {
			for(const auto& element : elements)
				byte_count += element.type.getByteCount();
		}

		inline void push(Element element) {
			elements.push_back(element);
			byte_count += element.type.getByteCount();
		}

		inline uint32_t getByteCount() const { return byte_count; }

		inline std::vector<Element>::iterator begin() { return elements.begin(); }
		inline std::vector<Element>::const_iterator begin() const { return elements.begin(); }
		inline std::vector<Element>::iterator end() { return elements.end(); }
		inline std::vector<Element>::const_iterator end() const { return elements.end(); }
	private:
		std::vector<Element> elements;
		uint32_t byte_count;
	};


	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual void setData(uint32_t size, void* data, BufferUsage usage) = 0;

		virtual void setLayout(const BufferLayout& layout) = 0;
	public:
		static Ref<VertexBuffer> create();
	};


	class IndexBuffer {
	public:
		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual uint32_t getCount() const = 0;

		virtual void setData(uint32_t count, void* data, BufferUsage usage) = 0;
	public:
		static Ref<IndexBuffer> create();
	};

}
