//#include "sdl/sdl.h"
//#include "sdl/sdl_image.h"

#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int main(int argc, char *argv[]) 
{
	SDL_Renderer *renderer = nullptr;
	SDL_Window *window = nullptr;

	// --- init ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "no es pot inicialitzar sdl";

	// --- window ---
	window = SDL_CreateWindow("my first sdl project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) throw "no es pot inicialitzar";

	// --- renderer ---
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) throw "no es pot inicialitzar";

	// --- renderer color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//init sdl_image

	//const uint8 imgflags{ img_init_png | img_init_jpg };
	//if (!(img_init(imgflags) & imgflags)) throw "error: sdl_image init";

	////quit
	//img_quit();

	SDL_Texture *bgtexture{ IMG_LoadTexture(renderer, "../../res/img/link.jpg") };
	if (bgtexture == nullptr) throw "no s'han pogut crear les textures";
	SDL_Rect bgrect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };


	bool quit = false;
	while (!quit) {
		//loop	
		//***********************************//
		SDL_RenderCopy(renderer, bgtexture, nullptr, &bgrect);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		//***********************************//
	}

	SDL_DestroyTexture(bgtexture);

	return 0;
}
