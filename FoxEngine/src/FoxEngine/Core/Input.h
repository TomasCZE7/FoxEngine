#pragma once
#include "fepch.h"

namespace FoxEngine
{

	class Input{
	private:
	public:
		static bool isKeyPressed(int keycode);
		static bool isMouseButtonPressed(int button);
		static std::pair<float, float> getMousePosition();
		static float getMouseX();
		static float getMouseY();

	};
	
}