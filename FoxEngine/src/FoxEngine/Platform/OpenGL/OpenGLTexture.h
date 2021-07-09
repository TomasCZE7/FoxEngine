#pragma once

#include "FoxEngine/Renderer/Texture.h"

namespace FoxEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	private:
		uint32_t m_Height, m_Width, m_RendererId;
		const std::string& m_Path;
	public:
		OpenGLTexture2D(const std::string& path);

		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual void Bind(uint32_t slot = 0) const override;
		
		virtual ~OpenGLTexture2D();
	};
}