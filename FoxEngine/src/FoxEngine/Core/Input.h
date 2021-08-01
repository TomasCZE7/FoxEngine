#pragma once
#include "fepch.h"

namespace FoxEngine
{

	class Input{
	private:
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	
	};
	
}