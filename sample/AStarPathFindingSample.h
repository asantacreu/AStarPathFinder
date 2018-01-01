#pragma once

//#include "resource.h"

#include "SDL.h"

class AStarPathFindingSample {
	public:
		AStarPathFindingSample();

		int Run();

	private:
		bool running;
		SDL_Window* screen;

		bool OnInit();
		void OnExecute();
		void OnEvent(SDL_Event* event);
		void OnLoop();
		void OnPaint();
		void OnCleanUp();
		void OnExit();

};