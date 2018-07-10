#pragma once

//#include <iostream>

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

#include "SDL.h"

class TextureManager;

class ENGINE_API Engine
{
public:
	Engine() { }
	~Engine() {}

	bool Intialize();
	void Update();
	void Shutdown();

	SDL_Window * GetWindow() { return m_window; }

	SDL_Renderer* GetRenderer() { return m_renderer; }

	bool IsQuit() { return m_isQuit; }

protected:
	bool m_isQuit = false;
	SDL_Window * m_window = nullptr;
	SDL_Renderer * m_renderer = nullptr;

};
