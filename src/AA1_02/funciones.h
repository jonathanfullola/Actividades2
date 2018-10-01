#include "tipos.h"

bool inside(int x1, int x2, int y1, int y2, type::vec2 mouse) {
	return mouse.x > x1 && mouse.x < x2 && mouse.y > y1 && mouse.y < y2;
}
