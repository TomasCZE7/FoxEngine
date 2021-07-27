#pragma once
#include "FoxEngine/Core/Core.h"

namespace FoxEngine
{
	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};
	
	class FrameBuffer
	{
	private:
	public:
		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererId() const = 0;
		
		static Ref<FrameBuffer> Create(const FrameBufferSpecification& specification);
	};
}