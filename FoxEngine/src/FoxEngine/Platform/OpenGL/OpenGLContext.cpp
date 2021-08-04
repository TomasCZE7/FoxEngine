#include "fepch.h"

#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace FoxEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: windowHandle(windowHandle){
		FOX_ASSERT(windowHandle, "Window is null!")
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(windowHandle);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FOX_CORE_ASSERT(gladStatus, "Failed to initialize GLAD!");
		FOX_CORE_INFO("Graphics card: {0}", glGetString(GL_RENDERER));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}
