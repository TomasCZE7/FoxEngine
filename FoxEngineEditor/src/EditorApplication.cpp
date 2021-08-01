#include <FoxEngine.h>
#include <FoxEngine/Core/EntryPoint.h>

#include "imgui/imgui.h"

#include "EditorLayer.h"


namespace FoxEngine
{
	class EditorApplication : public Application
	{

	public:
		EditorApplication()
			: Application("FoxEngine Editor"){
			PushLayer(new EditorLayer());
		}
		~EditorApplication()
		{

		}

	};

	Application* CreateApplication()
	{
		return new EditorApplication();
	}
}