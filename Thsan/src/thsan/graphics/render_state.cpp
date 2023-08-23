#include "pch.h"
#include "render_state.h"

namespace Thsan {

    std::weak_ptr<Shader> Thsan::ThsanRenderState2D::getShader()
    {
        return shader;
    }

    std::weak_ptr<Texture2D> Thsan::ThsanRenderState2D::getTexture2D()
    {
        return texture2D;
    }

    void Thsan::ThsanRenderState2D::setTexture2D(std::weak_ptr<Texture2D> texture2D)
    {
        this->texture2D = texture2D;
    }

    void Thsan::ThsanRenderState2D::setShader(std::weak_ptr<Shader> shader)
    {
        this->shader = shader;
    }
    
    std::shared_ptr<RenderState2D> create_renderState2D()
    {
        return std::make_shared<ThsanRenderState2D>();
    }
}
