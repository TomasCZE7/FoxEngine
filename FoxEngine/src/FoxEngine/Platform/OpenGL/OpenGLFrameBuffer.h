#pragma once

#include "FoxEngine/Renderer/FrameBuffer.h"

namespace FoxEngine
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	private:
		FrameBufferSpecification m_Specification;
		uint32_t m_RendererId;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& specification);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;
		
		virtual uint32_t GetColorAttachmentRendererId() const override { return	m_ColorAttachment; };

		const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
		
	};
}