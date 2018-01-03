#pragma once


#include "SDL.h"



class Cell {
	public:
		Cell(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		void Paint(SDL_Renderer* renderer);

		int GetX() const;
		int GetY() const;

		int f;
		int g;
		int h;

	private:
		int x;
		int y;
		SDL_Rect rect;
		SDL_Color color;

};