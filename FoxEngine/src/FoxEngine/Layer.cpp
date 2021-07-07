#include "fepch.h"
#include "Layer.h"

#include "Renderer/Renderer.h"

namespace FoxEngine {

	Layer::Layer(const std::string& name)
		: Name(name), Objects({})
	{

	}

	Layer::~Layer() {
	}

	void Layer::RenderObjects()
	{
		for(const auto& object : Objects)
		{
			object->GetShader()->Bind();
			Renderer::Submit(object->GetVertexArray());
		}
	}
}
