#include "engine.h"
#include "textureManager.h"
#include <assert.h>
#include "renderer.h"
#include "vector2D.h"
#include "matrix22.h"
#include "timer.h"
#include "math.h"
#include "inputManager.h"
#include <iostream>
#include "text.h"
#include "color.h"
#include <vector>
#include "textManager.h"
#include "audioSystem.h"
#include "physics.h"
#include "fileSystem.h"

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	
	FileSystem::Instance()->Intialize(this);
	Timer::Instance()->Intialize(this);
	Renderer::Instance()->Intialize(this);
	AudioSystem::Instance()->Intialize(this);
	InputManager::Instance()->Intialize(this);
	TextureManager::Instance()->Initialize(this);
	TextManager::Instance()->Initialize(this);
	Physics::Instance()->Initialize(this);

	return true;
}

void Engine::Shutdown()
{
	AudioSystem::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	Timer::Instance()->Shutdown();
	FileSystem::Instance()->Shutdown();
	
	
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->SetTImeScale(1.0f);
	InputManager::Instance()->Update();
	AudioSystem::Instance()->Update();
	Physics::Instance()->Update();
	FileSystem::Instance()->Update();

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
		}
	}

	SDL_PumpEvents();

	if (InputManager::Instance()->GetButtonState(SDL_SCANCODE_GRAVE) == InputManager::eButtonState::PRESSED)
	{
		m_isDebug = !m_isDebug;
	}
}

	

