#pragma once
#include "thsan/core.h"
#include <memory>

namespace Thsan {

	class Mesh;
	class Shader;
	class RenderTarget;
	class RenderState;
	class Framebuffer;
	class RenderManager;

	namespace renderCommands {

		class THSAN_API RenderCommand {
		public:
			RenderCommand() = default;
			RenderCommand(RenderCommand&) = default;
			virtual ~RenderCommand() = default;

			virtual void execute(const std::weak_ptr<RenderTarget> target, RenderManager& renderManager) = 0;
		protected:
		};

		class RenderMesh: public RenderCommand {
		public:
			RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader):
				mesh(mesh),
				shader(shader)
			{
			}

			~RenderMesh() = default;
			void execute(const std::weak_ptr<RenderTarget> target, RenderManager& renderManager) override;
		private:
			std::weak_ptr<Mesh> mesh;
			std::weak_ptr<Shader> shader;

		};

		class PushFramebuffer : public RenderCommand {
		public:
			PushFramebuffer(std::weak_ptr<Framebuffer> framebuffer) :
				framebuffer(framebuffer)
			{
			}

			~PushFramebuffer() = default;
			void execute(const std::weak_ptr<RenderTarget> target, RenderManager& renderManager) override;
		private:
			std::weak_ptr<Framebuffer> framebuffer;

		};

		class PopFramebuffer : public RenderCommand {
		public:
			PopFramebuffer() = default;
			~PopFramebuffer() = default;
			void execute(const std::weak_ptr<RenderTarget> target, RenderManager& renderManager) override;
		};

		inline THSAN_API std::unique_ptr<RenderCommand> create_renderMeshCommand(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> state);
		inline THSAN_API std::unique_ptr<RenderCommand> create_pushFramebufferCommand(std::weak_ptr<Framebuffer> framebuffer);
		inline THSAN_API std::unique_ptr<RenderCommand> create_popFramebufferCommand();
	}
}