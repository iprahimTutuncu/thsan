#include "pch.h"
#include "shader.h"
#include "thsan/graphics/graphic_api.h"
#include "platform/openGL/gl_shader.h"

#include <glm/gtc/type_ptr.hpp>
namespace Thsan {

	void Shader::setCamera(std::weak_ptr<tsm::AbsractCamera> camera)
	{
		std::shared_ptr<tsm::AbsractCamera> tmp_camera = camera.lock();
		if (tmp_camera) {
			setMat4("VP", tmp_camera->getViewProjection());
			setMat4("ciew", tmp_camera->getView());
			setVec3("camera_position", tmp_camera->getPosition());
			setVec3("camera_front", tmp_camera->getFront());
		}
		else
			TS_CORE_ERROR("error: in Shader::setCamera, camera.lock() return nullptr.");
	}

	std::string Shader::readFile(std::string path)
	{
		std::ifstream ifs(path);
		std::string str(std::istreambuf_iterator<char>{ifs}, {});
		return str;
	}

	THSAN_API std::shared_ptr<Shader> create_shader(const std::string& vs_path, const std::string& fs_path)
	{
		switch (get_graphic_API())
		{
		case GraphicAPI::openGL: return std::make_shared<GLShader>(vs_path, fs_path);
			case GraphicAPI::vulkan: return nullptr;
		};

		TS_CORE_ERROR("error: Shader not supported for the current graphic API");
		return nullptr;
	}
}
