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

}
