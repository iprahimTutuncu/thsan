#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <thsan/system/vector.h>
#include <string>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_uint2.hpp>
#include "drawable.h"

namespace tsm {
    class Transform;
}

namespace Thsan {
    
    class Texture2D;

    class THSAN_API SpriteAnimation : public Drawable {
    public:
        virtual void hide() = 0;
        virtual void show() = 0;
        virtual bool isHidden() const = 0;
        virtual void flipX() = 0;
        virtual void flipY() = 0;
        virtual bool isFlipX() const = 0;
        virtual bool isFlipY() const = 0;
        virtual void setTexture(std::shared_ptr<Texture2D> texture) = 0;
        virtual void setCurrAnimation(std::string name) = 0;
        virtual void add(glm::vec4 rect, float time) = 0;
        virtual void enableLoop() = 0;
        virtual void disableLoop() = 0;
        virtual void start(unsigned int from = 0, unsigned int to = 0) = 0;
        virtual void stop() = 0;
        virtual void reset() = 0;
        virtual void restart(unsigned int from = 0, unsigned int to = 0) = 0; //will call start() directly after reset()
        virtual bool isFinished() const = 0;
        virtual void setSpeed(float speed_factor) = 0;

        virtual bool hasAnimation(const std::string& name) const = 0;
        virtual unsigned int getFrameIndex() = 0;
        virtual int getFrameCount() = 0;
        virtual int getFrameWidth() = 0;
        virtual int getFrameHeight() = 0;
        virtual float getCurrentAnimationTimeDuration() = 0;
        virtual float getCurrentAnimationTimeReached() const = 0;
        virtual glm::uvec2 getSpriteSheetSize() const  = 0;
        virtual void update(const float& dt) = 0;

        virtual void setKeyColor(glm::vec4 color) = 0;
        virtual glm::vec4 getKeyColor() const = 0;

        virtual ~SpriteAnimation() = default;

        static std::shared_ptr<SpriteAnimation> create();
        static std::shared_ptr<SpriteAnimation> create(std::shared_ptr<Texture2D> texture);

        virtual void draw(const RenderTarget& target, RenderStates2D& states) const = 0;

        virtual std::shared_ptr<tsm::Transform> getTransform() = 0;
        virtual const glm::mat4 getTransformMatrix() const = 0;
    };

    class AnimationData;

    class SpriteAnimationImpl : public SpriteAnimation {
    public:
        SpriteAnimationImpl(); // Constructor

        void hide() override;
        void show() override;
        bool isHidden() const override;
        void flipX() override;
        void flipY() override;
        bool isFlipX() const override;
        bool isFlipY() const override;
        void setTexture(std::shared_ptr<Texture2D> texture) override;
        void setCurrAnimation(std::string name) override;
        void add(glm::vec4 rect, float time) override;
        void enableLoop() override;
        void disableLoop() override;
        void start(unsigned int from = 0, unsigned int to = 0) override;
        void stop() override;
        void reset() override;
        void restart(unsigned int from = 0, unsigned int to = 0) override;
        bool isFinished() const override;
        void setSpeed(float speed_factor) override;
        bool hasAnimation(const std::string& name) const override;
        unsigned int getFrameIndex() override;
        int getFrameCount() override;
        int getFrameWidth() override;
        int getFrameHeight() override;
        float getCurrentAnimationTimeDuration() override;
        float getCurrentAnimationTimeReached() const override;
        glm::uvec2 getSpriteSheetSize() const override;
        void update(const float& dt) override;
        void setKeyColor(glm::vec4 color) override;
        glm::vec4 getKeyColor() const override;

        void draw(const RenderTarget& target, RenderStates2D& states) const override;

        std::shared_ptr<tsm::Transform> getTransform() override;
        const glm::mat4 getTransformMatrix() const override;


        ~SpriteAnimationImpl() = default;
    private:
        void generate();
        std::unordered_map<std::string, std::unique_ptr<AnimationData>> animations;
        std::shared_ptr<Texture2D> texture;
        bool xFlip{ false };
        bool yFlip{ false };
        bool hidden{ false };
        bool stopped{ true };

        unsigned int from;
        unsigned int to;
        
        float speedFactor{ 1.f };

        std::string curr{};

        bool animationIsDone{ true };
        bool onNewFrame{ false };

        float tempsAccumuleFrame{0.f};
        float tempsAccumuleAnimation{0.f};

        float spritesheet_width;
        float spritesheet_height;

        glm::vec4 keyColor{0.f, 0.f, 0.f, 0.f};

        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<tsm::Transform> transform;
        std::shared_ptr<tsm::Transform> transform_result;
        std::shared_ptr<RenderStates2D> render_states;
    };
}