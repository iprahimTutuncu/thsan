#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace tsm {

	class Basis {
		glm::vec3 rows[3] = {
			glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(0.f, 0.f, 1.f)
		};

	public:
		Basis() = default;
		Basis(glm::dquat from);
		Basis(glm::vec3 from);
		Basis(glm::vec3 axis, float angle);
		Basis(glm::vec3 x_axis, glm::vec3 y_axis, glm::vec3 z_axis);

		inline const glm::vec3& operator[](int axis) const {
			return rows[axis];
		}

		inline glm::vec3& operator[](int axis) {
			return rows[axis];
		}

		void invert();
		void transpose();

		glm::vec3 slerp();
		Basis inverse() const;
		Basis transposed() const;

	};
}