#pragma once
#include "thsan/core.h"
#include <memory>
#include <vector>

namespace Thsan {
	class Shader;
	class Texture2D;
	//class Transform

	class THSAN_API RenderState2D {
	public:
		virtual inline std::weak_ptr<Shader> getShader() = 0;
		virtual inline std::weak_ptr<Texture2D> getTexture2D() = 0;
		virtual inline void setTexture2D(std::weak_ptr<Texture2D> texture2D) = 0;
		virtual inline void setShader(std::weak_ptr<Shader> shader) = 0;
	};

	class ThsanRenderState2D: public RenderState2D {
	public:
		// Inherited via RenderState2D
		virtual inline std::weak_ptr<Shader> getShader() override;

		virtual inline std::weak_ptr<Texture2D> getTexture2D() override;

		virtual inline void setTexture2D(std::weak_ptr<Texture2D> texture2D) override;

		virtual inline void setShader(std::weak_ptr<Shader> shader) override;
	private:
		std::weak_ptr<Shader> shader;
		std::weak_ptr<Texture2D> texture2D;
	};

	inline THSAN_API std::shared_ptr<RenderState2D> create_renderState2D();
}