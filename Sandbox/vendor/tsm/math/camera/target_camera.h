#pragma once
#include "abstract_camera.h"

namespace tsm {
	class TargetCamera: public AbsractCamera {
	public:
		TargetCamera() = default;
		~TargetCamera() = default;

		virtual void setTarget(const glm::vec3& target) = 0;
		virtual const glm::vec3 getTarget() const = 0;

		virtual void zoom(float amount) = 0;
		virtual void pan(float dx, float dy) = 0;
		virtual void move(float dx, float dy) = 0;

		// Inherited via AbsractCamera
		virtual void update() = 0;
		virtual void yaw(float rotation) override;
		virtual void roll(float rotation) override;
		virtual void pitch(float rotation) override;
		virtual void rotate(const float yaw, const float pitch, const float roll) override;
		virtual void setYaw(float rotation) override;
		virtual void setRoll(float rotation) override;
		virtual void setPitch(float rotation) override;
		virtual void setRotation(const float yaw, const float pitch, const float roll) override;

	protected:
		glm::vec3 target;

		float min_Ry = -60.f;
		float max_Ry =  60.f;

		float distance{ 10.f };
		float min_distance{ 0.1f };
		float max_distance{ 100.f };
	};
}