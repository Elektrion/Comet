#pragma once

#include "Comet/Core/Core.h"
#include "Comet/Core/Math.h"

namespace comet {

	class Texture {
	public:
		virtual inline ~Texture() noexcept = default;

		inline Texture(const Texture&) noexcept = delete;
		inline Texture(const Texture&&) noexcept = delete;
		inline Texture& operator=(const Texture&) noexcept = delete;
		inline Texture& operator=(const Texture&&) noexcept = delete;

		virtual void bind(uint32_t slot = 0) = 0;
		virtual void unBind(uint32_t slot = 0) = 0;
	protected:
		inline Texture() noexcept = default;
	};


	class Texture2D : public Texture {
	public:
		virtual uint32_t getWidth() const noexcept = 0;
		virtual uint32_t getHeight() const noexcept = 0;

		virtual glm::vec2 getTextureCoordsBottomLeft() const noexcept = 0;
		virtual glm::vec2 getTextureCoordsTopRight() const noexcept = 0;
		virtual std::array<glm::vec2, 4> getTextureCoords() const noexcept = 0;
	public:
		static Ref<Texture2D> create(const std::string& filename, bool pixelate = false);
		static Ref<Texture2D> create(uint32_t width, uint32_t height, uint32_t channels, const unsigned char* const pixels, bool pixelate = false);
		static Ref<Texture2D> create(uint32_t width, uint32_t height, glm::vec4 color, bool pixelate = false);
	};

	class SubTexture2D : public Texture2D {
	public:
		inline SubTexture2D(const Ref<Texture2D>& parent, uint32_t x, uint32_t y, uint32_t width, uint32_t height) noexcept : parent(parent), x(x), y(y), width(width), height(height) {}

		virtual inline void bind(uint32_t slot = 0) { parent->bind(slot); }
		virtual inline void unBind(uint32_t slot = 0) { parent->unBind(slot); }

		inline const Ref<Texture2D>& getParent() const noexcept { return parent; }

		inline uint32_t getX() const noexcept { return x; }
		inline uint32_t getY() const noexcept { return y; }

		virtual inline uint32_t getWidth() const noexcept { return width; }
		virtual inline uint32_t getHeight() const noexcept { return height; }

		virtual inline glm::vec2 getTextureCoordsBottomLeft() const noexcept { return { float(x) / float(parent->getWidth()), float(y) / float(parent->getHeight()) }; }
		virtual inline glm::vec2 getTextureCoordsTopRight() const noexcept { return { float(x + width) / float(parent->getWidth()), float(y + height) / float(parent->getHeight()) }; }
		virtual inline std::array<glm::vec2, 4> getTextureCoords() const noexcept { return {
			glm::vec2(float(x) / float(parent->getWidth()), float(y) / float(parent->getHeight())),
			glm::vec2(float(x + width) / float(parent->getWidth()), float(y) / float(parent->getHeight())), 
			glm::vec2(float(x + width) / float(parent->getWidth()), float(y + height) / float(parent->getHeight())), 
			glm::vec2(float(x) / float(parent->getWidth()), float(y + height) / float(parent->getHeight()))
		}; }
	public:
		static Ref<SubTexture2D> create(const Ref<Texture2D>& parent, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	private:
		Ref<Texture2D> parent;
		uint32_t x;
		uint32_t y;
		uint32_t width;
		uint32_t height;
	};

}
