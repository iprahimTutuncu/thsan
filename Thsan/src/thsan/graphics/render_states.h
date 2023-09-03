#pragma once
#include "thsan/core.h"
#include "thsan/system/vector.h"
#include <memory>
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_float3x3.hpp>

namespace tsm{
	class AbstractCamera;
	class Transform;
}

namespace Thsan {
	class Shader;
	class Texture2D;
	class View;

	class THSAN_API RenderStates {
	public:
		RenderStates() = default;
		virtual inline void bind() const = 0;
		virtual inline void unBind() const = 0;
	};

	class THSAN_API RenderStates2D: RenderStates {
	public:
		virtual inline std::weak_ptr<Shader> getShader() const = 0;
		virtual inline void setShader(std::weak_ptr<Shader> shader) = 0;
		virtual inline void setTransform(std::weak_ptr<tsm::Transform> transform) = 0;
		virtual inline void setView(std::weak_ptr<View> view) = 0;

		// H�rit� via RenderStates
		virtual void bind() const = 0;
		virtual void unBind() const = 0;
	};

	class THSAN_API RenderStates3D : RenderStates {
	public:
		virtual inline std::weak_ptr<Shader> getShader() const = 0;
		virtual inline std::weak_ptr<tsm::AbstractCamera> getCamera() const = 0;

		virtual inline void setShader(std::weak_ptr<Shader> shader) = 0;
		virtual inline void setCamera(std::weak_ptr<tsm::AbstractCamera> camera) = 0;
		virtual inline void setTransform(glm::mat4 transform) = 0;

		// H�rit� via RenderStates
		virtual void bind() const = 0;
		virtual void unBind() const = 0;
	};

	class RenderStates2DImpl : public RenderStates2D {
	public:
		// Inherited via RenderStates2D
		virtual inline std::weak_ptr<Shader> getShader() const override;

		virtual inline void setShader(std::weak_ptr<Shader> shader) override;

		virtual inline void setTransform(std::weak_ptr<tsm::Transform> transform) override;

		virtual inline void setView(std::weak_ptr<View> view) override;

		// H�rit� via RenderStates
		virtual void bind() const override;
		virtual void unBind() const override;

	private:
		int screenWidth{ 0 };
		int screenHeight{ 0 };
		std::weak_ptr<Shader> shader;
		std::weak_ptr<Texture2D> texture2D;
		std::weak_ptr<View> view;
		std::weak_ptr<tsm::Transform> transform;

	};

	class RenderStates3DImpl : public RenderStates3D {
	public:
		// Inherited via RenderStates3D
		virtual inline std::weak_ptr<Shader> getShader() const override;

		virtual inline std::weak_ptr<tsm::AbstractCamera> getCamera() const override;

		virtual inline void setShader(std::weak_ptr<Shader> shader) override;

		virtual inline void setCamera(std::weak_ptr<tsm::AbstractCamera> camera) override;

		virtual inline void setTransform(glm::mat4x4 transform) = 0;

		// H�rit� via RenderStates
		virtual void bind() const override;
		virtual void unBind() const override;

	private:
		std::weak_ptr<Shader> shader;
		std::weak_ptr<Texture2D> texture2D;
		std::weak_ptr<tsm::AbstractCamera> camera;
		glm::mat4x4 transform;
	};

	inline THSAN_API std::shared_ptr<RenderStates2D> create_renderstates2D();
	inline THSAN_API std::shared_ptr<RenderStates3D> create_renderstates3D();
}