#pragma once


#include "SDL.h"


#include "Cell.h"


class AStarPathFindingSample {
	public:
		AStarPathFindingSample();

		int Run();

	private:
		bool running;
		SDL_Window* screen;
		SDL_Renderer* renderer;

		Cell startCell;
		Cell endCell;

		bool OnInit();
		void OnExecute();
		void OnEvent(SDL_Event* event);
		void OnLoop();
		void OnPaint();
		void PaintBackground();
		void PaintGrid();
		void OnCleanUp();
		void OnExit();

};