#pragma once

#include "FoxEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace FoxEngine
{

	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* WindowHandle;
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		
		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
	
}