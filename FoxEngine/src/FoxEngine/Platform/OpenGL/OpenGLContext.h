#pragma once

#include "FoxEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace FoxEngine
{

	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* windowHandle;
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		
		virtual void init() override;
		virtual void swapBuffers() override;
	};
	
}