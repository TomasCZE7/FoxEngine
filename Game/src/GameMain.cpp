#include <iostream>
#include <FoxEngine.h>

class GameMain : public FoxEngine::Application
{

public:
	GameMain()
	{
		
	}
	~GameMain()
	{
		
	}
	
};

FoxEngine::Application* FoxEngine::CreateApplication()
{
	return new GameMain();
}