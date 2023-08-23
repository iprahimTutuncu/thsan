#pragma once
#include <glm/glm.hpp>

namespace tsm{
	class Transform {
	public:
		Transform() = default;
		~Transform() = default;

		void translate(glm::vec3 translation);
		void scale(glm::vec3 scale);

		void setTranslation(glm::vec3 translation);
		void setScale(glm::vec3 scale);

		void rotate(glm::vec3 rotate);

		const glm::mat4x4 getTransform();

		static glm::mat4 computeProjection(float Width, float Height);

	private:
		glm::mat4x4 translation_matrix;
		glm::mat4x4 scale_matrix;
	};

}



