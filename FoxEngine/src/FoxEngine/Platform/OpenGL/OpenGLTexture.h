#pragma once

#include "FoxEngine/Renderer/Texture.h"
#include <glad/glad.h>

namespace FoxEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	private:
		uint32_t height, width, rendererId;
		const std::string& path;
		GLenum internalFormat = GL_RGBA8, dataFormat = GL_RGBA;
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);

		virtual void setData(void* data, uint32_t size) override;

		virtual uint32_t getWidth() const override { return width; };
		virtual uint32_t getHeight() const override { return height; };
		virtual uint32_t getRendererId() const override { return rendererId; };
		
		virtual bool operator==(const Texture& other) const override
		{
			return rendererId == ((OpenGLTexture2D&)other).rendererId;
		}

		virtual void bind(uint32_t slot = 0) const override;
		
		virtual ~OpenGLTexture2D();
	};
}