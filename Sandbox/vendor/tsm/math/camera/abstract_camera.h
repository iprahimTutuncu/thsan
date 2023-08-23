#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace tsm {
	class AbsractCamera {
	public:
		AbsractCamera() = default;
		~AbsractCamera() = default;
		
		void setProjection(const float FOV, const float aspect_ratio, const float near_plane = 0.1f, const float far_plane = 1000.f);
		void setPosition(const glm::vec3& position);

		virtual void update() = 0;
		virtual void yaw(float rotation) = 0;
		virtual void roll(float rotation) = 0;
		virtual void pitch(float rotation) = 0;
		virtual void rotate(const float yaw, const float pitch, const float roll) = 0;

		virtual void setYaw(float rotation) = 0;
		virtual void setRoll(float rotation) = 0;
		virtual void setPitch(float rotation) = 0;
		virtual void setRotation(const float yaw, const float pitch, const float roll) = 0;

		static glm::mat4 GetMatrixUsingYawPitchRoll(const float yaw, const float pitch, const float roll);
		glm::mat4 getViewProjection();
		glm::mat4 getProjection();
		glm::mat4 getView();

		inline const float GetFOV() const;
		inline const float GetAspectRatio() const;
		inline const float getNearPlane() const;
		inline const float getFarPlane() const;

		const glm::vec3 getPosition() const;
		const glm::vec3 getFront() const;


	protected:
		static glm::vec3 UP;

		glm::vec3 up{ glm::vec3(0.f, 1.0f, 0.f) };
		glm::vec3 front{ glm::vec3(0.f, 0.f, 1.f) };
		glm::vec3 right{ glm::vec3(0.f, 0.f, 0.f) };

		glm::vec3 position{ glm::vec3(0.f, 0.f, 0.f) };

		glm::mat4 projection{ glm::mat4() };
		glm::mat4 view{ glm::mat4() };

		float aspect_ratio{1.0f};
		float near_plane{0.01f};
		float far_plane{1000.f};
		float FOV{53.f};

		float yaw_value{ 0.f };
		float roll_value{ 0.f };
		float pitch_value{ 0.f };
	};
}