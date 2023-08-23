#include "pch.h"
#include "thsan/graphics/texture.h"
#include "thsan/log.h"
#include "gl_framebuffer.h"
#include "GL/glew.h"
#include "gl_helper.h"

namespace Thsan {

    GLFramebuffer::GLFramebuffer() :
        Framebuffer(0, 0),
        fbo(0),
        renderbuffer_id(0)
    {
    }

    GLFramebuffer::GLFramebuffer(uint32_t width, uint32_t height) :
        fbo(0),
        renderbuffer_id(0),
        Framebuffer(width, height)
    {
        if(!create(width, height))
            TS_CORE_ERROR("error: GLFramebuffer::create(width, height) failed in constructor with size: {}, {}\n", width, height);
    }

    GLFramebuffer::~GLFramebuffer()
    {
        GL_CHECK(glDeleteFramebuffers(1, &fbo));
        GL_CHECK(glDeleteRenderbuffers(1, &renderbuffer_id));

        fbo = 0;
        renderbuffer_id = 0;
        texture2D = nullptr;
    }

    uint32_t GLFramebuffer::getSpecificGPU_FBO_ID()
    {
        return fbo;
    }

    std::shared_ptr<Texture2D> GLFramebuffer::getTexture2D()
    {
        return texture2D;
    }

    uint32_t GLFramebuffer::getRenderbufferID()
    {
        return renderbuffer_id;
    }

    bool GLFramebuffer::setActive(bool activate)
    {
        if (!activate) {
            GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
            isBind = false;
            return true;
        }

        GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
        GL_CHECK(glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a));
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
        isBind = true;
        return true;
    }

    bool GLFramebuffer::isActive()
    {
        return isBind;
    }

    inline void GLFramebuffer::setClearColor(glm::vec4 color)
    {
        clear_color = color;
    }

    inline void GLFramebuffer::setClearColor(float r, float g, float b, float a)
    {
        clear_color.r = r;
        clear_color.g = g;
        clear_color.b = b;
        clear_color.a = a;
    }

    inline glm::vec4 GLFramebuffer::getClearColor()
    {
        return clear_color;
    }

    bool GLFramebuffer::create(uint32_t width, uint32_t height)
    {
        bool success = true;

        GL_CHECK(glGenFramebuffers(1, &fbo));
        GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo));

        texture2D = create_texture2D();
        texture2D->create(vec2u{ width, height });

        GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2D->getSpecificRenderAPI_ID(), 0));
        GL_CHECK(glGenRenderbuffers(1, &renderbuffer_id));
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id));
        GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0));
        GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_id));

        uint32_t status = GL_CHECK(glCheckFramebufferStatus(GL_FRAMEBUFFER));

        if (status != GL_FRAMEBUFFER_COMPLETE) {
            TS_CORE_ERROR("error: failed to create framebuffer, buffer is not complet, status: {}\n", status);
            success = false;
        }

        GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        return success;
    }
}