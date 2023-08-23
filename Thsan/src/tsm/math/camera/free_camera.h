#pragma once
#include "abstract_camera.h"

namespace tsm {
	class FreeCamera: public AbsractCamera{
        
	public:
        FreeCamera() = default;
        ~FreeCamera() = default;

        void moveForward(float amount);
        void moveSide(float amount);
        void moveAbove(float amount);

        // Inherited via AbsractCamera
        virtual void update() override;

        virtual void yaw(float rotation) override;

        virtual void roll(float rotation) override;

        virtual void pitch(float rotation) override;

        virtual void rotate(const float yaw, const float pitch, const float roll) override;

        virtual void setYaw(float rotation) override;

        virtual void setRoll(float rotation) override;

        virtual void setPitch(float rotation) override;

        virtual void setRotation(const float yaw, const float pitch, const float roll) override;

	private:

        glm::vec3 translation{ glm::vec3(0.f, 0.f, 0.f) };

    };
}