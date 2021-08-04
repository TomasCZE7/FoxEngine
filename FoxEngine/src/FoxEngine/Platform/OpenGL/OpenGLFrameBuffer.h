#pragma once

#include "FoxEngine/Renderer/FrameBuffer.h"

namespace FoxEngine
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	private:
		FrameBufferSpecification specification;
		uint32_t rendererId = 0;
		uint32_t colorAttachment = 0;
		uint32_t depthAttachment = 0;
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& specification);
		virtual ~OpenGLFrameBuffer();

		void invalidate();

		virtual void bind() override;
		virtual void unbind() override;
		
		virtual void resize(uint32_t width, uint32_t height) override;
		
		virtual uint32_t getColorAttachmentRendererId() const override { return	colorAttachment; };

		const FrameBufferSpecification& getSpecification() const override { return specification; }
		
	};
}