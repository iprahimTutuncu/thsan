#include "pch.h"
#include "abstract_camera.h"

namespace tsm {

    glm::vec3 AbsractCamera::UP = glm::vec3(0.f, 1.f, 0.f);

    void AbsractCamera::setProjection(const float FOV, const float aspect_ratio, const float near_plane, const float far_plane)
    {
        this->FOV = FOV;
        this->aspect_ratio = aspect_ratio;
        this->near_plane = near_plane;
        this->far_plane = far_plane;

        projection = glm::perspective(glm::radians(FOV), aspect_ratio, near_plane, far_plane);
    }

    void AbsractCamera::setPosition(const glm::vec3& position)
    {
        this->position = position;
    }

    glm::mat4 AbsractCamera::GetMatrixUsingYawPitchRoll(const float yaw, const float pitch, const float roll)
    {
        return glm::yawPitchRoll(yaw, pitch, roll);
    }

    glm::mat4 AbsractCamera::getViewProjection()
    {
        return projection * view;
    }

    glm::mat4 AbsractCamera::getProjection()
    {
        return projection;
    }

    glm::mat4 AbsractCamera::getView()
    {
        return view;
    }

    const float AbsractCamera::GetFOV() const
    {
        return FOV;
    }

    const float AbsractCamera::GetAspectRatio() const
    {
        return aspect_ratio;
    }

    const float AbsractCamera::getNearPlane() const
    {
        return near_plane;
    }

    const float AbsractCamera::getFarPlane() const
    {
        return far_plane;
    }
    const glm::vec3 AbsractCamera::getPosition() const
    {
        return position;
    }
    const glm::vec3 AbsractCamera::getFront() const
    {
        return front;
    }
}