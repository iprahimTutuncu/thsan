#include <thsan/log.h>
#include <glm/glm.hpp>
#include <thsan/Input/ControlSetting.h>
#include <thsan/graphics/vertex.h>
#include <thsan/graphics/mesh.h>
#include <thsan/graphics/shader.h>
#include <thsan/graphics/texture.h>
#include <thsan/graphics/framebuffer.h>
#include <thsan/graphics/render_command.h>
#include <thsan/game.h>

#include "cool_stuff_state.h"


CoolStuffState::CoolStuffState(ts::Game* parent):
	ts::State(parent)
{
}

void CoolStuffState::init()
{
	parent->add(ts::Key::Left, ts::InputState::isPressed, ts::InputAction::left);
	parent->add(ts::Key::D, ts::InputState::isPressedNoRepeat, ts::InputAction::right);

	ts::Vertex vert;
	vert.position = ts::vec3f{ 0.1f, 0.4f, 0.35f };

	shader = ts::create_shader("media/shader/base.vert", "media/shader/base.frag");
	free_camera = std::make_unique<tsm::FreeCamera>();
	free_camera->setProjection(53.f, 1.0f);
	free_camera->setPosition(glm::vec3(0.f, 0.f, -5.f));
	free_camera->update();

	mesh = ts::create_mesh(4);
	ts::Mesh& mesh_ref = *mesh;
	mesh_ref[0].position = ts::vec3f{ 0.5f,  0.5f, 0.0f };
	mesh_ref[1].position = ts::vec3f{ 0.5f, -0.5f, 0.0f };
	mesh_ref[2].position = ts::vec3f{ -0.5f, -0.5f, 0.0f };
	mesh_ref[3].position = ts::vec3f{ -0.5f,  0.5f, 0.0f };

	mesh_ref[0].texCoord = ts::vec2f{ 1.0f, 0.0f };
	mesh_ref[1].texCoord = ts::vec2f{ 1.0f, 1.0f };
	mesh_ref[2].texCoord = ts::vec2f{ 0.0f, 1.0f };
	mesh_ref[3].texCoord = ts::vec2f{ 0.0f, 0.0f };

	mesh_ref[0].color = ts::vec4f{ 0.0, 0.0, 1.0, 1.0 };
	mesh_ref[1].color = ts::vec4f{ 0.0, 1.0, 0.0, 1.0 };
	mesh_ref[2].color = ts::vec4f{ 1.0, 0.0, 0.0, 1.0 };
	mesh_ref[3].color = ts::vec4f{ 1.0, 1.0, 1.0, 1.0 };


	mesh_ref.setIndices(std::vector<uint32_t>{0, 1, 3, 1, 2, 3});
	mesh_ref.generate();

	tex2D = ts::create_texture2D();
	tex2D->loadFromFile("ed");
	shader->bind();
	//shader->setTexture2D("texture", tex2D);
	shader->setVec3("don't exist", glm::vec3(1.0f, 0.0f, 0.0f));


	shader->setCamera(free_camera);

	framebuffer = ts::create_framebuffer(800, 600);

	/*
		camera = renderMng->create_camera(); // would be clean ngl
		camera.setPosition(glm::vec3(5.0f, 0.0, 0.0));
		//...more transform

		std::Shared_ptr<CameraFilter> camera_filter = renderMng->create_camera_filter();
		camera_filter->setTint(glm::vec4(1.0f, 0.0, 0.0, 0.5));

		camera->setFilter(camera_filter); //one at a time, only renders to one frambuffer idle
	*/
}

void CoolStuffState::input(const float& deltaTime, std::vector<ts::InputAction> inputActions)
{

	for (ts::InputAction i : inputActions) {
		parent->trace("yeah");
		if (i == Thsan::InputAction::left)
			parent->trace("yeah left clicked");
		if (i == Thsan::InputAction::right)
			parent->trace("yeah right clicked");
	}
}

void CoolStuffState::update(const float& deltaTime)
{
}

void CoolStuffState::draw(ts::RenderManager* target, const float& deltaTime)

{
	//free_camera->yaw(glm::radians(0.1f));
	free_camera->update();
	shader->setCamera(free_camera);

	target->clear();

	auto push_fb = ts::renderCommands::create_pushFramebufferCommand(framebuffer);
	target->submit(std::move(push_fb));

	//auto rc = ts::renderCommands::create_renderSceneCommand(std::vector<Model>, transform, shader);


	auto pop_fb = ts::renderCommands::create_popFramebufferCommand();
	target->submit(std::move(pop_fb));

	target->flush();
	target->clear();
	auto rc = ts::renderCommands::create_renderMeshCommand(mesh, shader);
	target->submit(std::move(rc));
	target->flush();

}

