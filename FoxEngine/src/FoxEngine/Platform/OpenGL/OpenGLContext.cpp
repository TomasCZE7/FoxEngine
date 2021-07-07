#include "fepch.h"

#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace FoxEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:WindowHandle(windowHandle){
		FOX_ASSERT(WindowHandle, "Window is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(WindowHandle);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FOX_CORE_ASSERT(gladStatus, "Failed to initialize GLAD!");
		FOX_CORE_INFO("Graphics card: {0}", glGetString(GL_RENDERER));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(WindowHandle);
	}
}
