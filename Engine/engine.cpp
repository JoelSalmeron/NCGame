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

Vector2D position(0.0f, 0.0f);
float angle = 0.0f;

Text* text;

//InputManager
//Renderer
//AudioSystem

bool Engine::Intialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	
	Timer::Instance()->Intialize(this);
	Renderer::Instance()->Intialize(this);
	//AudioSystem::Instance()->Intialize(this);
	InputManager::Instance()->Intialize(this);
	TextureManager::Instance()->Initialize(this);
	TextManager::Instance()->Initialize(this);

	text = TextManager::Instance()->CreateText("Hello", "..\\Content\\Courier.ttf", 24, Color::red);

	return true;
}

void Engine::Shutdown()
{
	//AudioSystem::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	Timer::Instance()->Shutdown();

	///SDL_DestroyRenderer(m_renderer);
	
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->SetTImeScale(10.0f);
	InputManager::Instance()->Update();



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

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (InputManager::Instance()->GetButtonAction(SDL_SCANCODE_A) == InputManager::eButtonState::PRESSED)
	{
		std::cout << "pressed\n";
	}

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if ((InputManager::Instance()->GetButtonAction(SDL_SCANCODE_A) == InputManager::eButtonState::PRESSED) || (InputManager::Instance()->GetButtonAction(SDL_SCANCODE_A) == InputManager::eButtonState::HELD))
	{
		angle -= 90.0f * Timer::Instance()->DeltaTime();
	}

	if (keystate[SDL_SCANCODE_RIGHT]) angle += 90.0f * Timer::Instance()->DeltaTime();

	Vector2D force = Vector2D::zero;
	if (keystate[SDL_SCANCODE_UP])   force.y = -200.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_DOWN]) force.y = 200.0f * Timer::Instance()->DeltaTime();

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force;

	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	text->SetText("Hello World", colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);

	//DRAW
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\Content\\car.bmp");
	Renderer::Instance()->DrawTexture(texture ,position, angle);

	Renderer::Instance()->EndFrame();






	//SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	//SDL_RenderClear(m_renderer);

	////Draw
	//SDL_Rect rect = { x, y, 64, 64 };
	//SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\Content\\cat.bmp");

	//SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	//SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
	////SDL_RenderFillRect(m_renderer, &rect);
	////SDL_RenderCopy(m_renderer, m_texture, nullptr, &rect);
	//SDL_RenderCopyEx(m_renderer, texture, nullptr, &rect, 45.0, nullptr, SDL_FLIP_NONE);

	//SDL_RenderPresent(m_renderer);
}

	

