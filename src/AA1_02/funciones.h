#include "tipos.h"

void randomGen(SDL_Rect &rupee) {
	rupee.x = rand() % ((800 - 170) - 170 ) + 70;
	rupee.y = rand() % ((600 - 90) - 90 ) + 50;
}

bool checkSquaresCollision(SDL_Rect rupee, SDL_Rect link) {
	
	if ((rupee.x + rupee.w >= link.x) &&  
		(rupee.x <= link.x + link.w) &&  
		(rupee.y <= link.y + link.h) &&  
		(rupee.y + rupee.h >= link.y))	  
		return true;
	return false;
}

bool checkSquarePointCollision(SDL_Rect square, type::vec2 point) {
	return point.x > square.x && point.x < square.x + square.w && point.y > square.y && point.y < square.y + square.h;
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
