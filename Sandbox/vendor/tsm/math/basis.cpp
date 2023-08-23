#include "pch.h"
#include "basis.h"

namespace tsm {
	Basis::Basis(glm::dquat from)
	{
	}
	Basis::Basis(glm::vec3 from)
	{
	}
	Basis::Basis(glm::vec3 axis, float angle)
	{
	}
	Basis::Basis(glm::vec3 x_axis, glm::vec3 y_axis, glm::vec3 z_axis)
	{
	}
	void Basis::invert()
	{
	}
	void Basis::transpose()
	{
	}
	glm::vec3 Basis::slerp()
	{
		return glm::vec3();
	}
	Basis Basis::inverse() const
	{
		return Basis();
	}
	Basis Basis::transposed() const
	{
		return Basis();
	}
}
