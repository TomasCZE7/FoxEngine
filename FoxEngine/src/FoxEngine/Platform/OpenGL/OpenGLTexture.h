#pragma once

#include "FoxEngine/Renderer/Texture.h"
#include <glad/glad.h>

namespace FoxEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	private:
		uint32_t m_Height, m_Width, m_RendererId;
		const std::string& m_Path;
		GLenum m_InternalFormat = GL_RGBA8, m_DataFormat = GL_RGBA;
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);

		virtual void SetData(void* data, uint32_t size) override;

		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };
		virtual uint32_t GetRendererId() const override { return m_RendererId; };
		
		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererId == ((OpenGLTexture2D&)other).m_RendererId;
		}

		virtual void Bind(uint32_t slot = 0) const override;
		
		virtual ~OpenGLTexture2D();
	};
}