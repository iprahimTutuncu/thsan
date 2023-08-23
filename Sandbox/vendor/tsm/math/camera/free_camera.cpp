#include "pch.h"
#include "free_camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>

namespace tsm {
	void FreeCamera::moveForward(float amount)
	{
		translation += amount * front;
	}

	void FreeCamera::moveSide(float amount)
	{
		translation += amount * right;
	}

	void FreeCamera::moveAbove(float amount)
	{
		translation += amount * up;
	}

	void FreeCamera::update()
	{
		glm::mat4 R = glm::yawPitchRoll(yaw_value, pitch_value, roll_value);
		front = glm::vec3(R * glm::vec4(0.f, 0.f, 1.f, 0.f));
		up = glm::vec3(R * glm::vec4(0.f, 1.f, 0.f, 0.f));
		position += translation;
		glm::vec3 target = position + front;
		right = glm::cross(front, up);
		view = glm::lookAt(position, target, up);
	}

	void FreeCamera::roll(float rotation)
	{
		roll_value += rotation;
	}
	void FreeCamera::pitch(float rotation)
	{
		pitch_value += rotation;
	}

	void FreeCamera::yaw(float rotation)
	{
		yaw_value += rotation;
	}
	void FreeCamera::rotate(const float yaw, const float pitch, const float roll)
	{
		yaw_value	+= yaw;
		pitch_value += pitch;
		roll_value	+= roll;
	}
	void FreeCamera::setYaw(float rotation)
	{
		this->yaw_value = rotation;
	}
	void FreeCamera::setRoll(float rotation)
	{
		this->roll_value = rotation;
	}
	void FreeCamera::setPitch(float rotation)
	{
		this->pitch_value = rotation;
	}
	void FreeCamera::setRotation(const float yaw, const float pitch, const float roll)
	{
		yaw_value	= yaw;
		pitch_value = pitch;
		roll_value	= roll;
	}

}
