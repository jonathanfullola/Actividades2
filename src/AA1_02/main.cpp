// Always needs to be included for an SDL app
#include <exception>
#include <iostream>
#include <string>
#include <time.h>
#include "funciones.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60
#define LIMIT_UP 15
#define LIMIT_DOWN 28
#define LIMIT_RIGHT 95
#define LIMIT_LEFT 95
#define NUM_TRIFORCE_WIDTH 60
#define DELAY 1000 / FPS
#define GAME_TIME 60



int main(int, char*[])
{
	type::vec2 v1;
	bool play = false;
	bool sound = true;
	bool UP, DOWN, RIGHT, LEFT,notUP,notDOWN,notRIGHT,notLEFT;
	UP = DOWN = RIGHT = LEFT = notUP = notRIGHT = notLEFT = false;
	bool UP2, DOWN2, RIGHT2, LEFT2, notUP2, notDOWN2, notRIGHT2, notLEFT2;
	UP2 = DOWN2 = RIGHT2 = LEFT2 = notUP2 = notRIGHT2 = notLEFT2 = false;
	int frameVelocity = 0;
	notDOWN = notDOWN2 = true;
	std::string timeST = " ";
	int gameTime = GAME_TIME;
	int u = 0, d = 0, u2 = 0, d2 = 0;

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
	//const Uint8 mixFlags( MIX_INIT_MP3 | MIX_INIT_OGG );
	//if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error:SDL_mixer init";
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	


	// --- SPRITES ---
		//Background
	SDL_ShowCursor(SDL_DISABLE);
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/zeldaBg.jpg") };
	if (bgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Texture* playBgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/field1.jpg") };
	if (playBgTexture == nullptr) throw "Error: bgTexture init";
	SDL_Texture *auxPlayBgTexture{};
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/cursor.png") };
	if (playerTexture == nullptr) throw "Error: bgTexture init";
	SDL_Rect playerRect{ 0,0,38,30 }; // x,y, width, heigth
	SDL_Rect playerTarget{ 0,0,50,50 };

	//-->Animated player1 ---
	SDL_Texture *playerSpriteTexture{ IMG_LoadTexture(m_renderer, "../../res/img/linkMinish1.png") };
	SDL_Rect playerSpriteRect, playerSpritePosition; 
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(playerSpriteTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 10; 
	frameHeight = textHeight / 8;
	playerSpritePosition.x = playerSpritePosition.y = 100;
	playerSpriteRect.x = playerSpriteRect.y = 0;
	playerSpritePosition.h = playerSpriteRect.h = frameHeight;
	playerSpritePosition.w = playerSpriteRect.w = frameWidth;
	int frameTimeSprite = 0;

	//-->Animated player2 ---
	SDL_Texture *player2SpriteTexture{ IMG_LoadTexture(m_renderer, "../../res/img/linkMinish2.png") };
	SDL_Rect player2SpriteRect, player2SpritePosition;
	int textWidth2, textHeight2, frameWidth2, frameHeight2;
	SDL_QueryTexture(player2SpriteTexture, NULL, NULL, &textWidth2, &textHeight2);
	frameWidth2 = textWidth2 / 10;
	frameHeight2 = textHeight2 / 8;
	player2SpritePosition.x = 600; 
	player2SpritePosition.y = 100;
	player2SpriteRect.x = player2SpriteRect.y = 0;
	player2SpritePosition.h = player2SpriteRect.h = frameHeight2;
	player2SpritePosition.w = player2SpriteRect.w = frameWidth2;

	//-->Animated triforce ---
	SDL_Texture *triforceSprite{ IMG_LoadTexture(m_renderer, "../../res/img/trifuerza.png") };
	SDL_Rect triforceRect, triforcePosition;
	int triforceWidth, triforceHeight, triforceFrameWidth, triforceFrameHeight;
	SDL_QueryTexture(triforceSprite, NULL, NULL, &triforceWidth, &triforceHeight);
	triforceFrameWidth = triforceWidth / NUM_TRIFORCE_WIDTH;
	triforceFrameHeight = triforceHeight / 1;
	triforcePosition.x = 550;
	triforcePosition.y = 200;
	triforceRect.x = triforceRect.y = 0;
	triforcePosition.w = triforceRect.w = triforceFrameWidth;
	triforcePosition.h = triforceRect.h = triforceFrameHeight;

	//-->Animated rupee ---
	SDL_Texture *rupeeSprite{ IMG_LoadTexture(m_renderer, "../../res/img/rupee1.png") };
	SDL_Rect rupeeRect, rupeePosition;
	int rupeeWidth, rupeeHeight, rupeeFrameWidth, rupeeFrameHeight;
	SDL_QueryTexture(rupeeSprite, NULL, NULL, &rupeeWidth, &rupeeHeight);
	rupeeFrameWidth = rupeeWidth / 5;
	rupeeFrameHeight = rupeeHeight / 1;
	rupeeRect.x = rupeeRect.y = 0;
	randomGen(rupeePosition);
	rupeePosition.w = rupeeRect.w = rupeeFrameWidth;
	rupeePosition.h = rupeeRect.h = rupeeFrameHeight;

	//-->Animated units player1---
	SDL_Texture *uSprite{ IMG_LoadTexture(m_renderer, "../../res/img/zeldaFont.png") };
	SDL_Rect uRect, uPosition;
	int uWidth, uHeight, uFrameWidth, uFrameHeight;
	SDL_QueryTexture(uSprite, NULL, NULL, &uWidth, &uHeight);
	uFrameWidth = uWidth / 10;
	uFrameHeight = uHeight / 1;
	uRect.x = uRect.y = 0;
	uPosition.x = 55;
	uPosition.y = 50;
	uPosition.w = uRect.w = uFrameWidth;
	uPosition.h = uRect.h = uFrameHeight;

	//-->Animated decenas player1---
	SDL_Texture *dSprite{ IMG_LoadTexture(m_renderer, "../../res/img/zeldaFont.png") };
	SDL_Rect dRect, dPosition;
	int dWidth, dHeight, dFrameWidth, dFrameHeight;
	SDL_QueryTexture(dSprite, NULL, NULL, &dWidth, &dHeight);
	dFrameWidth = dWidth / 10;
	dFrameHeight = dHeight / 1;
	dRect.x = dRect.y = 0;
	dPosition.x = 20;
	dPosition.y = 50;
	dPosition.w = dRect.w = dFrameWidth;
	dPosition.h = dRect.h = dFrameHeight;

	//-->Animated units player2---
	SDL_Texture *u2Sprite{ IMG_LoadTexture(m_renderer, "../../res/img/zeldaFont.png") };
	SDL_Rect u2Rect, u2Position;
	int u2Width, u2Height, u2FrameWidth, u2FrameHeight;
	SDL_QueryTexture(u2Sprite, NULL, NULL, &u2Width, &u2Height);
	u2FrameWidth = u2Width / 10;
	u2FrameHeight = u2Height / 1;
	u2Rect.x = u2Rect.y = 0;
	u2Position.x = SCREEN_WIDTH - 20 - u2FrameWidth;
	u2Position.y = 50;
	u2Position.w = u2Rect.w = u2FrameWidth;
	u2Position.h = u2Rect.h = u2FrameHeight;

	//-->Animated decenas player2---
	SDL_Texture *d2Sprite{ IMG_LoadTexture(m_renderer, "../../res/img/zeldaFont.png") };
	SDL_Rect d2Rect, d2Position;
	int d2Width, d2Height, d2FrameWidth, d2FrameHeight;
	SDL_QueryTexture(d2Sprite, NULL, NULL, &d2Width, &d2Height);
	d2FrameWidth = d2Width / 10;
	d2FrameHeight = d2Height / 1;
	d2Rect.x = d2Rect.y = 0;
	d2Position.x = SCREEN_WIDTH - 55 - d2FrameWidth;
	d2Position.y = 50;
	d2Position.w = d2Rect.w = d2FrameWidth;
	d2Position.h = d2Rect.h = d2FrameHeight;


	// --- TEXT ---
	//obrir font
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/Triforce.ttf",80) };
	if (font == nullptr) throw "No es pot inicialitzar the TTF_Font";

	//crear superficie 
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font,"The legend of Zelda", SDL_Color{ 255,255,255,255 }) };
	if (tmpSurf == nullptr) throw "Unable to create the title text";
	SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font,"The legend of Zelda", SDL_Color{ 255,255,0,255 }) };
	//if (tmpSurf == nullptr) throw "Unable to create the SDL text";
	SDL_Texture *hoverTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Texture *auxTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Rect textRect{ 57,50, tmpSurf->w,tmpSurf->h };

	//play button
	tmpSurf = { TTF_RenderText_Blended(font,"Play", SDL_Color{255,255,255,255}) };
	SDL_Texture *playTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font,"Play", SDL_Color{255,255,0,255}) };
	SDL_Texture *hoverPlayTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Texture *auxPlayTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Rect playRect{ 80,200, tmpSurf->w,tmpSurf->h };

	//sound off button
	tmpSurf = { TTF_RenderText_Blended(font,"Sound off", SDL_Color{255,255,255,255}) };
	SDL_Texture *soundOffTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font,"Sound off", SDL_Color{255,255,0,255}) };
	SDL_Texture *hoverSoundOffTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };

	//sound on button
	tmpSurf = { TTF_RenderText_Blended(font,"Sound on", SDL_Color{255,255,255,255}) };
	SDL_Texture *soundOnTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font,"Sound on", SDL_Color{255,255,0,255}) };
	SDL_Texture *hoverSoundOnTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Texture *auxSoundTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) }; //auxsound para off y on
	SDL_Rect soundRect{ 80,300, tmpSurf->w,tmpSurf->h };

	//exit button
	tmpSurf = { TTF_RenderText_Blended(font,"Exit", SDL_Color{255,255,255,255}) };
	SDL_Texture *exitTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	tmpSurf = { TTF_RenderText_Blended(font,"Exit", SDL_Color{255,255,0,255}) };
	SDL_Texture *hoverExitTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Texture *auxExitTexture{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Rect exitRect{ 80,400, tmpSurf->w,tmpSurf->h };

	//time number
	tmpSurf = { TTF_RenderText_Blended(font,"0", SDL_Color{255,255,0,255}) };
	SDL_Texture *timeValue{ SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
	SDL_Rect timeRect{ (SCREEN_WIDTH/2 - tmpSurf->w/2),40, tmpSurf->w,tmpSurf->h };

	// --- AUDIO ---
	Mix_Music *music = Mix_LoadMUS("../../res/au/zeldaMain.mp3");
	if (!music) throw "Error: not music found";
	Mix_Music *playMusic = Mix_LoadMUS("../../res/au/zeldaNes.mp3");
	if (!playMusic) throw "Error: not play music found";

	Mix_Chunk *rupee = Mix_LoadWAV("../../res/au/rupee.mp3");

	
	Mix_VolumeMusic(MIX_MAX_VOLUME /20);

	// --- DELTATIME --- 
	clock_t lastTime = clock();
	float timeDown = 1, deltaTime = 0;

	// --- GAME LOOP ---
	SDL_Event event;
	Uint32 frames;
	bool isRunning = true;
	int frameTime = 0;
	Mix_PlayMusic(music, -1);
	srand(time(NULL));
	while (isRunning) {
		frames = SDL_GetTicks();
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				playerTarget.x = event.motion.x - 50;
				playerTarget.y = event.motion.y - 50;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (inside(playRect.x, playRect.x + playRect.w, playRect.y, playRect.y + playRect.h, v1) && !play) {
					play = true;
					u = u2 = d = d2 = 0;
					gameTime = GAME_TIME;
					Mix_PauseMusic();
					Mix_PlayMusic(playMusic, -1);
					break;
				}
				if (inside(soundRect.x, soundRect.x + soundRect.w, soundRect.y, soundRect.y + soundRect.h, v1) && !play) {
					sound = !sound;
					break;
				}
				if (inside(exitRect.x, exitRect.x + exitRect.w, exitRect.y, exitRect.y + exitRect.h, v1) && !play)
					isRunning = false;
				break;
			case SDL_KEYDOWN:
				//player1
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				else if (event.key.keysym.sym == SDLK_w) { UP = true; notUP = notDOWN = notRIGHT = notLEFT = false;	}
				else if (event.key.keysym.sym == SDLK_s) { DOWN = true; notUP = notDOWN = notRIGHT = notLEFT = false; }
				else if (event.key.keysym.sym == SDLK_d) { RIGHT = true; notUP = notDOWN = notRIGHT = notLEFT = false; }
				else if (event.key.keysym.sym == SDLK_a) { LEFT = true; notUP = notDOWN = notRIGHT = notLEFT = false; }
				
				//player2
				else if (event.key.keysym.sym == SDLK_UP) { UP2 = true; notUP2 = notDOWN2 = notRIGHT2 = notLEFT2 = false; }
				else if (event.key.keysym.sym == SDLK_DOWN)	{DOWN2 = true; notUP2 = notDOWN2 = notRIGHT2 = notLEFT2 = false;}
				else if (event.key.keysym.sym == SDLK_RIGHT) { RIGHT2 = true; notUP2 = notDOWN2 = notRIGHT2 = notLEFT2 = false; }
				else if (event.key.keysym.sym == SDLK_LEFT) { LEFT2 = true; notUP2 = notDOWN2 = notRIGHT2 = notLEFT2 = false; }
				break;

			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_w) { UP = false; notUP = true; }
				else if (event.key.keysym.sym == SDLK_s) { DOWN = false; notDOWN = true; }
				else if (event.key.keysym.sym == SDLK_d) { RIGHT = false; notRIGHT = true; }
				else if (event.key.keysym.sym == SDLK_a) { LEFT = false; notLEFT = true; }

				else if (event.key.keysym.sym == SDLK_UP) { UP2 = false; notUP2 = true; }
				else if (event.key.keysym.sym == SDLK_DOWN) { DOWN2 = false; notDOWN2 = true; }
				else if (event.key.keysym.sym == SDLK_RIGHT) { RIGHT2 = false; notRIGHT2 = true; }
				else if (event.key.keysym.sym == SDLK_LEFT) { LEFT2 = false; notLEFT2 = true; }
				break;
			default:;
			}
		}

		// UPDATE
		playerRect.x += (playerTarget.x - playerRect.x) + 46;
		playerRect.y += (playerTarget.y - playerRect.y) + 48;
		v1.x = event.motion.x;
		v1.y = event.motion.y;

		//deltaTime
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		if (play && timeDown <= 0) { gameTime--; timeDown = 1; }
		if (gameTime <= 0) play = false;


		if (!play) {

			//text
			if (inside(textRect.x, textRect.x + textRect.w, textRect.y, textRect.y + textRect.h, v1))
				auxTexture = hoverTexture;
			else
				auxTexture = textTexture;

			//play
			if (inside(playRect.x, playRect.x + playRect.w, playRect.y, playRect.y + playRect.h, v1))
				auxPlayTexture = hoverPlayTexture;
			else
				auxPlayTexture = playTexture;

			//sonido
			if (!sound) {
				Mix_PauseMusic();
				if (inside(soundRect.x, soundRect.x + soundRect.w, soundRect.y, soundRect.y + soundRect.h, v1))
					auxSoundTexture = hoverSoundOffTexture;
				else
					auxSoundTexture = soundOffTexture;
			}
			else {
				Mix_ResumeMusic();
				if (inside(soundRect.x, soundRect.x + soundRect.w, soundRect.y, soundRect.y + soundRect.h, v1))
					auxSoundTexture = hoverSoundOnTexture;
				else
					auxSoundTexture = soundOnTexture;
			}

			//exit
			if (inside(exitRect.x, exitRect.x + exitRect.w, exitRect.y, exitRect.y + exitRect.h, v1))
				auxExitTexture = hoverExitTexture;
			else
				auxExitTexture = exitTexture;

			auxPlayBgTexture = bgTexture;
		}
		else {
			auxPlayBgTexture = playBgTexture;
		}

		//if (!checkCollision(playerSpritePosition, player2SpritePosition)) {
		//movement player1
		if (UP && !checkUpCollision(playerSpritePosition.y, LIMIT_UP)) { playerSpritePosition.y -= 3; }
		else if (DOWN && !checkDownCollision(playerSpritePosition.y + frameHeight, SCREEN_HEIGHT - LIMIT_DOWN)) { playerSpritePosition.y += 3; }
		else if (RIGHT && !checkRightCollision(playerSpritePosition.x + frameWidth, SCREEN_WIDTH - LIMIT_RIGHT)) { playerSpritePosition.x += 3; }
		else if (LEFT && !checkLeftCollision(playerSpritePosition.x, LIMIT_LEFT)) { playerSpritePosition.x -= 3; }

		//movement player2
		if (UP2 && !checkUpCollision(player2SpritePosition.y, LIMIT_UP)) { player2SpritePosition.y -= 3; }
		else if (DOWN2 && !checkDownCollision(player2SpritePosition.y + frameHeight, SCREEN_HEIGHT - LIMIT_DOWN)) { player2SpritePosition.y += 3; }
		else if (RIGHT2 && !checkRightCollision(player2SpritePosition.x + frameWidth, SCREEN_WIDTH - LIMIT_RIGHT)) { player2SpritePosition.x += 3; }
		else if (LEFT2 && !checkLeftCollision(player2SpritePosition.x, LIMIT_LEFT)) { player2SpritePosition.x -= 3; }
		//}else 
		
		//sprite update
		frameTimeSprite++;

		if (!play) frameVelocity = 40;
		else frameVelocity = 9;

		if (FPS / frameTimeSprite <= frameVelocity)
		{
			frameTimeSprite = 0;

			if (!play) {
				triforceRect.x += triforceFrameWidth;
				if (triforceRect.x >= triforceWidth)
					triforceRect.x = 0;

				triforceRect.y = 0;
				if (triforceRect.x >= triforceFrameWidth * NUM_TRIFORCE_WIDTH) triforceRect.x = 0;
			}
			else {

				rupeeRect.x += rupeeFrameWidth;
				if (rupeeRect.x >= rupeeWidth) rupeeRect.x = 0;
				rupeeRect.y = 0;
				if (rupeeRect.x >= rupeeFrameWidth * 5) rupeeRect.x = 0;

				//player 1 sprite control
					//update x
				playerSpriteRect.x += frameWidth;
				if (playerSpriteRect.x >= textWidth)
					playerSpriteRect.x = 0;

				//update y
				if (UP) {
					playerSpriteRect.y = frameHeight * 6;
					if (playerSpriteRect.x >= frameWidth * 9) playerSpriteRect.x = 0;
				}
				else if (DOWN) {
					playerSpriteRect.y = frameHeight * 4;
					if (playerSpriteRect.x >= frameWidth * 9) playerSpriteRect.x = 0;
				}
				else if (RIGHT) {
					playerSpriteRect.y = frameHeight * 7;
					if (playerSpriteRect.x >= frameWidth * 9) playerSpriteRect.x = 0;
				}
				else if (LEFT) {
					playerSpriteRect.y = frameHeight * 5;
					if (playerSpriteRect.x >= frameWidth * 9) playerSpriteRect.x = 0;
				}
				else if (notUP) {
					playerSpriteRect.y = frameHeight * 2;
					playerSpriteRect.x = 0;
				}
				else if (notDOWN) {
					playerSpriteRect.y = 0;
					playerSpriteRect.x = 0;
				}
				else if (notRIGHT) {
					playerSpriteRect.y = frameHeight * 3;
					playerSpriteRect.x = 0;
				}
				else if (notLEFT) {
					playerSpriteRect.y = frameHeight * 1;
					playerSpriteRect.x = 0;
				}

				//player 2 sprite control
				//update x
				player2SpriteRect.x += frameWidth2;
				if (player2SpriteRect.x >= textWidth2)
					player2SpriteRect.x = 0;

				//update y
				if (UP2) {
					player2SpriteRect.y = frameHeight2 * 6;
					if (player2SpriteRect.x >= frameWidth2 * 9) player2SpriteRect.x = 0;
				}
				else if (DOWN2) {
					player2SpriteRect.y = frameHeight2 * 4;
					if (player2SpriteRect.x >= frameWidth2 * 9) player2SpriteRect.x = 0;
				}
				else if (RIGHT2) {
					player2SpriteRect.y = frameHeight2 * 7;
					if (player2SpriteRect.x >= frameWidth2 * 9) player2SpriteRect.x = 0;
				}
				else if (LEFT2) {
					player2SpriteRect.y = frameHeight2 * 5;
					if (player2SpriteRect.x >= frameWidth2 * 9) player2SpriteRect.x = 0;
				}
				else if (notUP2) {
					player2SpriteRect.y = frameHeight2 * 2;
					player2SpriteRect.x = 0;
				}
				else if (notDOWN2) {
					player2SpriteRect.y = 0;
					player2SpriteRect.x = 0;
				}
				else if (notRIGHT2) {
					player2SpriteRect.y = frameHeight2 * 3;
					player2SpriteRect.x = 0;
				}
				else if (notLEFT2) {
					player2SpriteRect.y = frameHeight2 * 1;
					player2SpriteRect.x = 0;
				}

			}

			//score int to string
			timeST = std::to_string(gameTime);
			const char *timeNumber = timeST.c_str();

			//modify tmpsurf time
			tmpSurf = { TTF_RenderText_Blended(font,timeNumber, SDL_Color{255,255,0,255}) };
			timeValue = { SDL_CreateTextureFromSurface(m_renderer,tmpSurf) };
			timeRect = { (SCREEN_WIDTH / 2 - tmpSurf->w / 2),35, tmpSurf->w,tmpSurf->h };

			//check if a player collides with the rupee
			if (checkCollision(rupeePosition, playerSpritePosition) ) {
				u++;
				if (u >= 10) { d++; u = 0; }
				randomGen(rupeePosition);
				Mix_PlayChannel(-1, rupee, 0);
			}
			if (checkCollision(rupeePosition, player2SpritePosition)) {
				u2++;
				if (u2 >= 10) { d2++; u2 = 0; }
				randomGen(rupeePosition);
				Mix_PlayChannel(-1, rupee, 0);
			}	
		}

		uRect.x = uFrameWidth * u;
		dRect.x = dFrameWidth * d;
		u2Rect.x = u2FrameWidth * u2;
		d2Rect.x = d2FrameWidth * d2;


		// DRAW
		SDL_RenderClear(m_renderer);

		//Background
		SDL_RenderCopy(m_renderer, auxPlayBgTexture, nullptr, &bgRect);

		if (!play) {
			//pintar titulo + hoverTitulo
			SDL_RenderCopy(m_renderer, auxTexture, nullptr, &textRect);
			//pintar play + hoverPlay
			SDL_RenderCopy(m_renderer, auxPlayTexture, nullptr, &playRect);
			//pintar sound + hover
			SDL_RenderCopy(m_renderer, auxSoundTexture, nullptr, &soundRect);
			//pintar exit + hoverPlay
			SDL_RenderCopy(m_renderer, auxExitTexture, nullptr, &exitRect);
			//pintar triforce
			SDL_RenderCopy(m_renderer, triforceSprite, &triforceRect, &triforcePosition);
		}
		else {
			//player1
			SDL_RenderCopy(m_renderer, playerSpriteTexture, &playerSpriteRect, &playerSpritePosition);
			//player2
			SDL_RenderCopy(m_renderer, player2SpriteTexture, &player2SpriteRect, &player2SpritePosition);
			//animated rupee
			SDL_RenderCopy(m_renderer, rupeeSprite, &rupeeRect, &rupeePosition);
			//score player1
			SDL_RenderCopy(m_renderer, uSprite, &uRect, &uPosition);
			SDL_RenderCopy(m_renderer, dSprite, &dRect, &dPosition);
			//score player2
			SDL_RenderCopy(m_renderer, u2Sprite, &u2Rect, &u2Position);
			SDL_RenderCopy(m_renderer, d2Sprite, &d2Rect, &d2Position);
			//pintar time
			SDL_RenderCopy(m_renderer, timeValue, nullptr, &timeRect);
		}

		//cursor
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);
		SDL_RenderPresent(m_renderer);

		//frame control
		frameTime = SDL_GetTicks() - frames;                                            
		if (frameTime < DELAY) SDL_Delay((int)(DELAY - frameTime));

	}

	// --- DESTROY ---
	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);
	Mix_FreeChunk(rupee);

	SDL_DestroyTexture(playTexture);
	SDL_DestroyTexture(hoverPlayTexture);
	SDL_DestroyTexture(soundOffTexture);
	SDL_DestroyTexture(hoverSoundOffTexture);
	SDL_DestroyTexture(soundOnTexture);
	SDL_DestroyTexture(hoverSoundOnTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(hoverTexture);
	SDL_DestroyTexture(auxExitTexture);
	SDL_DestroyTexture(auxPlayBgTexture);
	SDL_DestroyTexture(auxPlayTexture);
	SDL_DestroyTexture(auxSoundTexture);
	SDL_DestroyTexture(auxTexture);
	SDL_DestroyTexture(playerSpriteTexture);
	SDL_DestroyTexture(player2SpriteTexture);
	SDL_DestroyTexture(triforceSprite);
	SDL_DestroyTexture(rupeeSprite);

	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}