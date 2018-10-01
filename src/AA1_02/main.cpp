// Always needs to be included for an SDL app
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_audio.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>
#include "funciones.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

////////
////////int main(int argc, char *argv[]) 
////////{
////////	SDL_Renderer *renderer = nullptr;
////////	SDL_Window *window = nullptr;
////////
////////	// --- init ---
////////	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "no es pot inicialitzar sdl";
////////
////////	// --- window ---
////////	window = SDL_CreateWindow("my first sdl project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
////////	if (window == nullptr) throw "no es pot inicialitzar";
////////
////////	// --- renderer ---
////////	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
////////	if (renderer == nullptr) throw "no es pot inicialitzar";
////////
////////	// --- renderer color
////////	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
////////
////////	//init sdl_image
////////
////////	//const uint8 imgflags{ img_init_png | img_init_jpg };
////////	//if (!(img_init(imgflags) & imgflags)) throw "error: sdl_image init";
////////
////////	////quit
////////	//img_quit();
////////
////////	SDL_Texture *bgtexture{ IMG_LoadTexture(renderer, "../../res/img/link.jpg") };
////////	if (bgtexture == nullptr) throw "no s'han pogut crear les textures";
////////	SDL_Rect bgrect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
////////
////////
////////	bool quit = false;
////////	while (!quit) {
////////		//loop	
////////		//***********************************//
////////		SDL_RenderCopy(renderer, bgtexture, nullptr, &bgrect);
////////		SDL_RenderPresent(renderer);
////////		SDL_RenderClear(renderer);
////////		//***********************************//
////////	}
////////
////////	SDL_DestroyTexture(bgtexture);
////////
////////	return 0;
////////}


int main(int, char*[])
{
	type::vec2 v1;
	bool play = false;

	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_ttf";

		
	//-->SDL_Mix



	// --- SPRITES ---
		//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/cursor.png") };
	if (playerTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect playerRect{ 0,0,38,30 }; // x,y, width, heigth
	SDL_Rect playerTarget{ 0,0,50,50 };

	//-->Animated Sprite ---

	// --- TEXT ---
	//obrir font
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };
	if (font == nullptr) throw "No es pot inicialitzar the TTF_Font";

	//crear superficie 
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font,"My first SDL game", SDL_Color{ 255,150,0,255 }) };
	if (tmpSurf == nullptr) throw "Unable to create the title text";
	SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font,"My first SDL Hover", SDL_Color{ 100,150,150,255 }) };
	//if (tmpSurf == nullptr) throw "Unable to create the SDL text";
	SDL_Texture *hoverTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Rect textRect{ 100,50, tmpSurf->w,tmpSurf->h };

	//play button
	tmpSurf = { TTF_RenderText_Blended(font,"Play", SDL_Color{255,150,0,255}) };
	SDL_Texture *playTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font,"Play", SDL_Color{255,50,0,100}) };
	SDL_Texture *hoverPlayTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Rect playRect{ 100,200, tmpSurf->w,tmpSurf->h };

	//sound button
	tmpSurf = { TTF_RenderText_Blended(font,"Sound", SDL_Color{255,150,0,255}) };
	SDL_Texture *soundTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font,"Sound", SDL_Color{255,50,0,100}) };
	SDL_Texture *hoverSoundTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Rect soundRect{ 100,300, tmpSurf->w,tmpSurf->h };

	//exit button
	tmpSurf = { TTF_RenderText_Blended(font,"Exit", SDL_Color{255,150,0,255}) };
	SDL_Texture *exitTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font,"Exit", SDL_Color{255,50,0,100}) };
	SDL_Texture *hoverExitTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Rect exitRect{ 100,400, tmpSurf->w,tmpSurf->h };

	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);

	// --- AUDIO ---
	
	

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				break;
			case SDL_MOUSEMOTION: 
				//playerRect.x = event.motion.x; playerRect.y = event.motion.y; 
				playerTarget.x = event.motion.x - 50;
				playerTarget.y = event.motion.y - 50;
				break;
			
			default:;
			}
		}		

		// UPDATE
		playerRect.x += (playerTarget.x - playerRect.x) + 46;
		playerRect.y += (playerTarget.y - playerRect.y) + 48;
		v1.x = event.motion.x;
		v1.y = event.motion.y;


		// DRAW
		SDL_RenderClear(m_renderer);
		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);

		//pintar titulo + hoverTitulo
		if(inside(textRect.x,textRect.x + textRect.w, textRect.y, textRect.y + textRect.h,v1))
			SDL_RenderCopy(m_renderer, hoverTexture, nullptr, &textRect);
		else
			SDL_RenderCopy(m_renderer, textTexture, nullptr, &textRect);

		//pintar play + hoverPlay
		if (inside(playRect.x, playRect.x + playRect.w, playRect.y, playRect.y + playRect.h,v1))
			SDL_RenderCopy(m_renderer, hoverPlayTexture, nullptr, &playRect);
		else
			SDL_RenderCopy(m_renderer, playTexture, nullptr, &playRect);

		//pintar sound + hover
		if (inside(soundRect.x, soundRect.x + soundRect.w, soundRect.y, soundRect.y + soundRect.h, v1))
			SDL_RenderCopy(m_renderer, hoverSoundTexture, nullptr, &soundRect);
		else
			SDL_RenderCopy(m_renderer, soundTexture, nullptr, &soundRect);

		//pintar exit + hoverPlay
		if (inside(exitRect.x, exitRect.x + exitRect.w, exitRect.y, exitRect.y + exitRect.h, v1))
			SDL_RenderCopy(m_renderer, hoverExitTexture, nullptr, &exitRect);
		else
			SDL_RenderCopy(m_renderer, exitTexture, nullptr, &exitRect);

		//cursor (kinton)
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);
		SDL_RenderPresent(m_renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(textTexture);
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}