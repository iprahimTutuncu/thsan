#pragma once
#include <thsan/state/State.h>

#include "tsm/tsm.h"

#define ts Thsan

namespace ts {
	class Mesh;
	class Shader;
	class Texture2D;
	class Framebuffer;
}

namespace tsm {
	class FreeCamera;
}

class CoolStuffState : public ts::State {
public:
	CoolStuffState(ts::Game* parent);
	~CoolStuffState() = default;


	// Inherited via State
	virtual void init() override;

	virtual void input(const float& deltaTime, std::vector<ts::InputAction> inputActions) override;

	virtual void update(const float& deltaTime) override;

	virtual void draw(ts::RenderManager* target, const float& deltaTime) override;

private:
	std::shared_ptr<ts::Mesh> mesh;
	std::shared_ptr<ts::Shader> shader;
	std::shared_ptr<ts::Texture2D> tex2D;
	std::shared_ptr<ts::Framebuffer> framebuffer;
	std::shared_ptr<tsm::FreeCamera> free_camera;
};