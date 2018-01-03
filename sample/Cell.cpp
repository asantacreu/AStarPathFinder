
#include "stdafx.h"

#include "Cell.h"


#include "Defines.h"



Cell::Cell(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	this->x = x;
	this->y = y;

	rect.x = x * CELL_SIZE;
	rect.y = y * CELL_SIZE;
	rect.w = CELL_SIZE;
	rect.h = CELL_SIZE;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	f = 0;
	g = 0;
	h = 0;
}



void Cell::Paint(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}



int Cell::GetX() const {
	return x;
}



int Cell::GetY() const {
	return y;
}