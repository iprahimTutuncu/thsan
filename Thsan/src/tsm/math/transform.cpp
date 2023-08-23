#include "pch.h"
#include "transform.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>


namespace tsm {
	void Transform::translate(glm::vec3 translation)
	{
		translation_matrix = glm::translate(translation_matrix, translation);
	}
	void Transform::scale(glm::vec3 scale)
	{
		scale_matrix = glm::scale(scale_matrix, scale);
	}
	void Transform::setTranslation(glm::vec3 translation)
	{
		translation_matrix = glm::translate(glm::identity<glm::mat4x4>(), translation);
	}
	void Transform::setScale(glm::vec3 scale)
	{
		scale_matrix = glm::scale(glm::identity<glm::mat4x4>(), scale);

	}
	void Transform::rotate(glm::vec3 rotate)
	{
	}
	const glm::mat4x4 Transform::getTransform()
	{
		return translation_matrix * scale_matrix;
	}
	glm::mat4 Transform::computeProjection(float Width, float Height)
	{
		return glm::perspective(glm::radians(45.0f), Width / Height, 0.1f, 100.f);
	}
}