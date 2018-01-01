#pragma once


#include "SDL.h"



class Cell {
	public:
		Cell(unsigned int x, unsigned int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		void Paint(SDL_Renderer* renderer);

	private:
		SDL_Rect rect;
		SDL_Color color;

};