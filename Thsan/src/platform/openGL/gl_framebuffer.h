#pragma once

#include "thsan/graphics/Framebuffer.h"

namespace Thsan {

	class Texture2D;

	class GLFramebuffer: public Framebuffer {
	public:
		GLFramebuffer();
		GLFramebuffer(uint32_t width, uint32_t height);
		~GLFramebuffer();
		// Inherited via Framebuffer
		virtual bool create(uint32_t width, uint32_t height) override;
		virtual uint32_t getSpecificGPU_FBO_ID() override;
		virtual std::shared_ptr<Texture2D> getTexture2D() override;
		virtual uint32_t getRenderbufferID() override;

		virtual bool setActive(bool activate = true) override;
		virtual bool isActive() override;

		virtual inline void setClearColor(glm::vec4 color) override;
		virtual inline void setClearColor(float r, float g, float b, float a = 1.0f) override;
		virtual inline glm::vec4 getClearColor() override;
	private:
		bool isBind{ false };
		uint32_t fbo;
		uint32_t renderbuffer_id;
		glm::vec4 clear_color{ glm::vec4(1.0f) };
		std::shared_ptr<Texture2D> texture2D;



	};
}