#pragma once
#include "thsan/core.h"
#include <glm/glm.hpp>

namespace tsm {
    class THSAN_API Transform {
    public:
        Transform() = default;
        virtual ~Transform() = default;

        virtual void setTranslation(const glm::vec3& translation) = 0;
        virtual void setScale(const glm::vec3& scale) = 0;
        virtual void setRotation(const glm::vec3& rotate) = 0;
        virtual void setOrigin(const glm::vec3& origin) = 0;

        virtual void rotate(const glm::vec3& rotate) = 0;
        virtual void scale(const glm::vec3& rotate) = 0;
        virtual void translate(const glm::vec3& rotate) = 0;


        virtual void setTransform(const glm::mat4& transform) = 0;
        virtual const glm::mat4 getTransform() = 0;

        static std::shared_ptr<Transform> create();
    };

    class TransformImpl : public Transform {
    public:
        TransformImpl();

        virtual void setTranslation(const glm::vec3& translation) override;
        virtual void setScale(const glm::vec3& scale) override;
        virtual void setRotation(const glm::vec3& rotate) override;
        virtual void setOrigin(const glm::vec3& origin) override;

        virtual void rotate(const glm::vec3& rotate) override;
        virtual void scale(const glm::vec3& rotate) override;
        virtual void translate(const glm::vec3& rotate) override;

        virtual void setTransform(const glm::mat4& transform) override;
        virtual const glm::mat4 getTransform() override;

    private:
        glm::mat4 translate_to_origin_matrix;
        glm::mat4 translate_back_matrix;
        glm::mat4 translation_matrix;
        glm::mat4 scale_matrix;
        glm::mat4 rotation_matrix;
        glm::mat4 transform_matrix;
    };
}

