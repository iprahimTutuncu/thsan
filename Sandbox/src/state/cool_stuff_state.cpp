#include <thsan/log.h>
#include <glm/glm.hpp>
#include <thsan/Input/ControlSetting.h>
#include <thsan/graphics/vertex.h>
#include <thsan/graphics/mesh.h>
#include <thsan/graphics/shader.h>
#include <thsan/graphics/texture.h>
#include <thsan/graphics/framebuffer.h> 
#include <thsan/graphics/render_command.h>
#include <thsan/graphics/render_states.h>
#include <thsan/graphics/tilemap.h>
#include <thsan/graphics/view.h>
#include <thsan/game.h>
#include <tsm/math/transform.h>

#include "cool_stuff_state.h"
#include "../ressource_manager/texture2D_manager.h"


CoolStuffState::CoolStuffState(ts::Game* parent):
	ts::State(parent)
{ 
}
std::shared_ptr<Thsan::Mesh> generateColoredGrid(unsigned int columns, unsigned int rows, float cellSize) {
	// Calculate the total number of vertices and indices
	unsigned int vertexCount = (rows + 1) * (columns + 1);
	unsigned int indexCount = rows * columns * 6; // Each cell has 2 triangles (6 indices)

	// Create a mesh with the calculated vertex count
	std::shared_ptr<Thsan::Mesh> gridMesh = Thsan::create_mesh(vertexCount);

	// Create vertices for the grid
	std::vector<Thsan::Vertex> vertices;
	for (unsigned int i = 0; i <= rows; ++i) {
		for (unsigned int j = 0; j <= columns; ++j) {
			float x = static_cast<float>(j) * cellSize;
			float y = static_cast<float>(i) * cellSize;

			// Calculate a unique color based on row and column indices
			float r = static_cast<float>(i) / static_cast<float>(rows);
			float g = static_cast<float>(j) / static_cast<float>(columns);
			float b = 0.5f; // You can adjust the blue component as needed

			// Create a vertex with position and color information
			Thsan::Vertex vertex;
			vertex.position = Thsan::vec3f{ x, y, 0.0f };
			vertex.color = Thsan::vec4f{ r, g, b, 1.0f };
			vertex.texCoord = Thsan::vec2f{r,g};

			vertices.push_back(vertex);
		}
	}

	// Set the grid vertices
	gridMesh->setVertices(vertices);

	// Create indices for the grid
	std::vector<uint32_t> indices;
	for (unsigned int i = 0; i < rows; ++i) {
		for (unsigned int j = 0; j < columns; ++j) {
			// Define indices for the two triangles forming each cell
			uint32_t topLeft = i * (columns + 1) + j;
			uint32_t topRight = topLeft + 1;
			uint32_t bottomLeft = (i + 1) * (columns + 1) + j;
			uint32_t bottomRight = bottomLeft + 1;

			// Triangle 1
			indices.push_back(topLeft);
			indices.push_back(bottomRight);
			indices.push_back(bottomLeft);

			// Triangle 2
			indices.push_back(topLeft);
			indices.push_back(topRight);
			indices.push_back(bottomRight);
		}
	}

	// Set the grid indices
	gridMesh->setIndices(indices);

	return gridMesh;
}

std::shared_ptr<Thsan::Mesh> createQuadMesh(float x, float y, float width, float height, const Thsan::vec4f& color) {
	// Create a mesh with 4 vertices (one for each corner of the quad)
	std::shared_ptr<Thsan::Mesh> quadMesh = Thsan::create_mesh(4);

	// Create vertices for the quad
	std::vector<Thsan::Vertex> vertices(4);

	// Vertex 0 - Top Left
	vertices[0].position = Thsan::vec3f{ x, y, 0.0f };
	vertices[0].color = color;
	vertices[0].texCoord = Thsan::vec2f{ 0.f , 0.0f };

	// Vertex 1 - Top Right
	vertices[1].position = Thsan::vec3f{ x + width, y, 0.0f };
	vertices[1].color = color;
	vertices[1].texCoord = Thsan::vec2f{ 1.0f, 0.0f };

	// Vertex 2 - Bottom Right
	vertices[2].position = Thsan::vec3f{ x + width, y + height, 0.0f };
	vertices[2].color = color;
	vertices[2].texCoord = Thsan::vec2f{ 1.0f, 1.0f };

	// Vertex 3 - Bottom Left
	vertices[3].position = Thsan::vec3f{ x, y + height, 0.0f };
	vertices[3].color = color;
	vertices[3].texCoord = Thsan::vec2f{ 0.0f, 1.0f };

	// Set the quad vertices
	quadMesh->setVertices(vertices);

	// Create indices for the quad (two triangles)
	std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };
	quadMesh->setIndices(indices);

	return quadMesh;
}

std::shared_ptr<Thsan::Mesh> generateColoredCube(float size) {
	// Calculate the vertices and indices for a cube
	std::vector<Thsan::Vertex> vertices;
	std::vector<uint32_t> indices;

	// Define the eight vertices of the cube
	// You can adjust the colors as needed
	Thsan::vec3f positions[] = {
		{-size, -size, -size}, // Vertex 0
		{size, -size, -size},  // Vertex 1
		{size, size, -size},   // Vertex 2
		{-size, size, -size},  // Vertex 3
		{-size, -size, size},  // Vertex 4
		{size, -size, size},   // Vertex 5
		{size, size, size},    // Vertex 6
		{-size, size, size}    // Vertex 7
	};

	Thsan::vec4f colors[] = {
		{1.0f, 0.0f, 0.0f, 1.0f}, // Red
		{0.0f, 1.0f, 0.0f, 1.0f}, // Green
		{0.0f, 0.0f, 1.0f, 1.0f}, // Blue
		{1.0f, 1.0f, 0.0f, 1.0f}, // Yellow
		{1.0f, 0.0f, 1.0f, 1.0f}, // Magenta
		{0.0f, 1.0f, 1.0f, 1.0f}, // Cyan
		{0.5f, 0.5f, 0.5f, 1.0f}, // Gray
		{1.0f, 1.0f, 1.0f, 1.0f}  // White
	};

	// Define the indices for the cube's triangles (12 triangles, 36 indices)
	uint32_t cubeIndices[] = {
		0, 1, 2, 2, 3, 0, // Front face
		1, 5, 6, 6, 2, 1, // Right face
		5, 4, 7, 7, 6, 5, // Back face
		4, 0, 3, 3, 7, 4, // Left face
		3, 2, 6, 6, 7, 3, // Top face
		4, 5, 1, 1, 0, 4  // Bottom face
	};

	// Create the cube's vertices
	for (int i = 0; i < 8; ++i) {
		Thsan::Vertex vertex;
		vertex.position = positions[i];
		vertex.color = colors[i];
		vertices.push_back(vertex);
	}

	// Create the cube's mesh
	std::shared_ptr<Thsan::Mesh> cubeMesh = Thsan::create_mesh(vertices.size());
	cubeMesh->setVertices(vertices);
	cubeMesh->setIndices(std::vector<uint32_t>(cubeIndices, cubeIndices + 36));

	return cubeMesh;
}



void CoolStuffState::init()
{
	parent->add(ts::Key::Left, ts::InputState::isPressed, ts::InputAction::left);
	parent->add(ts::Key::Right, ts::InputState::isPressed, ts::InputAction::right);
	parent->add(ts::Key::Up, ts::InputState::isPressed, ts::InputAction::up);
	parent->add(ts::Key::Down, ts::InputState::isPressed, ts::InputAction::down);
	parent->add(ts::Key::Q, ts::InputState::isPressed, ts::InputAction::rotateLeft);
	parent->add(ts::Key::E, ts::InputState::isPressed, ts::InputAction::rotateRight);

	shader = ts::create_shader("media/shader/base2D.vert", "media/shader/base2D.frag");

	mesh = createQuadMesh(0.f, 0.f, 100.f, 100.f, Thsan::vec4f{1.0f, 0.0f, 0.0f, 1.0f});
	mesh->generate();

	tex2D = RessourceManager::Texture2DManager::get(RessourceManager::Texture2DManager::default_texture_white);

	framebuffer = ts::create_framebuffer(800, 600);

	tilemap = Thsan::create_tilemap();
	const int tiles[] =
	{ 
		1, 1, 1,
		1, 1, 1,
		1, 1, 1
	};
	tilemap->load(tiles);

	renderstates = Thsan::create_renderstates2D();
	renderstates->setShader(shader);
	renderstates->setTexture2D(tex2D);

	//make a default if not exist
	view = Thsan::View::create(0, 0, 800, 600, 1.f, 0.f);
	view->setZoom(1.f);
	renderstates->setView(view);

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
	static float x = 0.f;
	static float y = 0.f;
	static float r = 0.f;
	static float t = 0.f;
	for (ts::InputAction i : inputActions) {
		if (i == Thsan::InputAction::left)
			x += -200 * deltaTime;
		if (i == Thsan::InputAction::right)
			x += 200 * deltaTime;
		if (i == Thsan::InputAction::up)
			y += -200 * deltaTime;
		if (i == Thsan::InputAction::down)
			y += 200 * deltaTime;
		if (i == Thsan::InputAction::rotateLeft)
			r += 10 * deltaTime;
		if (i == Thsan::InputAction::rotateRight)
			r -= 10 * deltaTime;
	
		parent->trace("x: " + std::to_string(x) + ", y: " + std::to_string(y));
	}

	t += 10.f * deltaTime;
	transform = tsm::Transform::create();
	transform->setTranslation(glm::vec3(x, y, 0.0));
	transform->setOrigin(glm::vec3(50.f, 50.f, 0.f));
	transform->setRotation(glm::vec3(0.0, 0.0, t));
	renderstates->setTransform(transform);
}

void CoolStuffState::update(const float& deltaTime)
{
	static float t = 0.f;
	t += deltaTime;


}

void CoolStuffState::draw(ts::RenderManager* target, const float& deltaTime)
{
	target->clear();
	framebuffer->setClearColor(0.1f, 0.1f, 0.2f, 0.3f);
	auto push_fb = ts::renderCommands::create_pushFramebufferCommand(framebuffer);
	target->submit(std::move(push_fb));

	//auto rc = ts::renderCommands::create_renderSceneCommand(std::vector<Model>, transform, shader);


	auto pop_fb = ts::renderCommands::create_popFramebufferCommand();
	target->submit(std::move(pop_fb));

	auto rc = ts::renderCommands::create_renderMeshCommand(mesh, renderstates);
	//auto rc = ts::renderCommands::create_renderDrawableCommand(tilemap, renderstates);
	target->submit(std::move(rc));
	target->flush();

}

