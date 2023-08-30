#include "pch.h"
#include "transform.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/quaternion_common.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace tsm {

    TransformImpl::TransformImpl() {
        // Initialize transformation matrices
        translation_matrix = glm::mat4(1.0f);
        scale_matrix = glm::mat4(1.0f);
        rotation_matrix = glm::mat4(1.0f);
        transform_matrix = glm::mat4(1.0f);
        translate_to_origin_matrix = glm::mat4(1.0f);
        translate_back_matrix = glm::mat4(1.0f);
    }

    void TransformImpl::translate(const glm::vec3& translation) {
        // Update the translation matrix
        translation_matrix = glm::translate(glm::mat4(1.0f), translation);
    }

    void TransformImpl::scale(const glm::vec3& scale) {
        // Update the scale matrix
        scale_matrix = glm::scale(glm::mat4(1.0f), scale);
    }

    void TransformImpl::setTranslation(const glm::vec3& translation) {
        // Set the translation matrix directly
        translation_matrix = glm::translate(glm::mat4(1.0f), translation);
    }

    void TransformImpl::setScale(const glm::vec3& scale) {
        // Set the scale matrix directly
        scale_matrix = glm::scale(glm::mat4(1.0f), scale);
    }

    void TransformImpl::setRotation(const glm::vec3& rotate) {
        // Set the rotation matrix directly
        glm::mat4 x_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 y_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 z_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
        rotation_matrix = z_rotation * y_rotation * x_rotation;
    }

    void TransformImpl::setOrigin(const glm::vec3& origin)
    {
        this->translate_to_origin_matrix = glm::translate(glm::mat4(1.0f), -origin);
        this->translate_back_matrix = glm::translate(glm::mat4(1.0f), origin);
    }

    void TransformImpl::rotate(const glm::vec3& rotate) {
        // Apply additional rotation to the existing rotation matrix
        glm::mat4 x_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 y_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 z_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
        rotation_matrix = z_rotation * y_rotation * x_rotation * rotation_matrix;
    }

    void TransformImpl::setTransform(const glm::mat4& transform)
    {
        //maybe have the individual compoenent in th set transform
        //a meidter, voir SFML comment y font

        transform_matrix = transform_matrix;
        
        glm::vec3 translation, skew, scale;
        glm::quat rotation_quat;
        glm::vec4 perspective;
        glm::decompose(transform, scale, rotation_quat, translation, skew, perspective);

        // Update local variables
        translation_matrix = glm::translate(glm::mat4(1.0f), translation);
        scale_matrix = glm::scale(glm::mat4(1.0f), scale);

        // Calculate rotation matrix from the quaternion
        rotation_matrix = glm::mat4_cast(rotation_quat);

        // Set the transform matrix
        transform_matrix = transform;

        translate_to_origin_matrix = glm::translate(glm::mat4(1.0f), -translation);
        translate_back_matrix = glm::translate(glm::mat4(1.0f), translation);

    }

    const glm::mat4 TransformImpl::getTransform() {

        glm::mat4 R = translate_back_matrix * rotation_matrix * translate_to_origin_matrix;
        transform_matrix = translation_matrix * R * scale_matrix;
        return transform_matrix;
    }


    std::shared_ptr<Transform> Transform::create()
    {
        return std::make_shared<TransformImpl>();
    }


}
