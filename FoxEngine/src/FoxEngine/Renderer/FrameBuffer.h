#pragma once
#include "FoxEngine/Core/Core.h"

namespace FoxEngine
{
	struct FrameBufferSpecification
	{
		uint32_t width, height;
		uint32_t samples = 1;

		bool swapChainTarget = false;
	};
	
	class FrameBuffer
	{
	private:
	public:
		virtual const FrameBufferSpecification& getSpecification() const = 0;

		virtual ~FrameBuffer() = default;
		
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual uint32_t getColorAttachmentRendererId() const = 0;
		virtual void resize(uint32_t width, uint32_t height) = 0;

		static Ref<FrameBuffer> create(const FrameBufferSpecification& specification);
	};
}
