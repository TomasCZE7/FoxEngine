#include "fepch.h"
#include "RenderCommand.h"

#include "FoxEngine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace FoxEngine
{
	RendererAPI* RenderCommand::rendererApi = new OpenGLRendererAPI;
}
