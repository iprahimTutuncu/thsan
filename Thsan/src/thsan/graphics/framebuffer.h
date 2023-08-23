#pragma once
#include "thsan/core.h"
#include <cstdint>
#include <memory>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

namespace Thsan {

	class Texture2D;

	class THSAN_API Framebuffer
	{
	public:
		Framebuffer() = default;
		Framebuffer(uint32_t width, uint32_t height);
		virtual ~Framebuffer() = default;

		virtual bool create(uint32_t width, uint32_t height) = 0;
		virtual inline uint32_t getSpecificGPU_FBO_ID() = 0;
		virtual inline std::shared_ptr<Texture2D> getTexture2D() = 0;
		virtual inline uint32_t getRenderbufferID() = 0;

		inline uint32_t getWidth();
		inline uint32_t getHeight();
		inline glm::uvec2 getSize();
		virtual inline void setClearColor(glm::vec4 color) = 0;
		virtual inline void setClearColor(float r, float g, float b, float a = 1.0f) = 0;
		virtual inline glm::vec4 getClearColor() = 0;

		[[nodiscard]] virtual bool setActive(bool activate = true) = 0;
		virtual bool isActive() = 0;

	protected:
		uint32_t width{ 0 };
		uint32_t height{ 0 };
	};

	THSAN_API std::shared_ptr<Framebuffer> create_framebuffer(uint32_t width = 0, uint32_t height = 0);

}