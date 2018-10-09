#include "tipos.h"

bool inside(int x1, int x2, int y1, int y2, type::vec2 mouse) {
	return mouse.x > x1 && mouse.x < x2 && mouse.y > y1 && mouse.y < y2;
}

void randomGen(SDL_Rect &rupee) {
	rupee.x = rand() % ((800 - 170) - 170 ) + 70;
	rupee.y = rand() % ((600 - 90) - 90 ) + 50;
}

bool checkCollision(SDL_Rect rupee, SDL_Rect link) {
	
	if ((rupee.x + rupee.w >= link.x) &&  
		(rupee.x <= link.x + link.w) &&  
		(rupee.y <= link.y + link.h) &&  
		(rupee.y + rupee.h >= link.y))	  
		return true;
	return false;
}

bool checkUpCollision(int playerY, int limitY) {
	return playerY <= limitY;
}

bool checkDownCollision(int playerY, int limitY) {
	return playerY >= limitY;
}

bool checkLeftCollision(int playerX, int limitX) {
	return playerX <= limitX;
}

bool checkRightCollision(int playerX, int limitX) {
	return playerX >= limitX;
}
