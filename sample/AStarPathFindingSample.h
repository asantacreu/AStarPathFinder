#pragma once

//#include "resource.h"

#include "SDL.h"

class AStarPathFindingSample {
	public:
		AStarPathFindingSample();

		bool Init();
		int Run();

	private:
		SDL_Window* screen;
};