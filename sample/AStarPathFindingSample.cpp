
#include "stdafx.h"

#include "AStarPathFindingSample.h"

#pragma comment(linker, "/INCLUDE:_mainCRTStartup")


#define GRID_WIDTH 640
#define GRID_HEIGHT 480

#define CELL_SIZE 16



int _tmain(int argc, char* argv[]) {
	AStarPathFindingSample aStarPathFindingSample;

	return aStarPathFindingSample.Run();
}



AStarPathFindingSample::AStarPathFindingSample() {
	running = true;
	screen = NULL;
}



int AStarPathFindingSample::Run() {
	bool initialized = OnInit();
	if (initialized) {
		OnExecute();

		return 0;
	}

	return -1;
}



bool AStarPathFindingSample::OnInit() {
	int sdlInitialized = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdlInitialized >= 0) {
		SDL_CreateWindowAndRenderer(640, 480, 0, &screen, &renderer);

		if (screen != NULL && renderer != NULL) {
			return true;
		}
	}

	return false;
}



void AStarPathFindingSample::OnExecute() {
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			OnEvent(&event);
		}

		OnLoop();

		OnPaint();
	}

	OnCleanUp();
}



void AStarPathFindingSample::OnEvent(SDL_Event* event) {
	switch (event->type) {
		case SDL_QUIT: {
			OnExit();
			break;
		}
	}
}



void AStarPathFindingSample::OnLoop() {

}



void AStarPathFindingSample::OnPaint() {
	PaintBackground();

	PaintGrid();

	SDL_RenderPresent(renderer);
}



void AStarPathFindingSample::PaintBackground() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderClear(renderer);
}



void AStarPathFindingSample::PaintGrid() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	for (int x = 0; x < GRID_WIDTH; x += CELL_SIZE) {
		for (int y = 0; y < GRID_HEIGHT; y += CELL_SIZE) {
			SDL_RenderDrawLine(renderer, x, 0, x, GRID_HEIGHT);
			SDL_RenderDrawLine(renderer, 0, y, GRID_WIDTH, y);
		}
	}
}



void AStarPathFindingSample::OnCleanUp() {
	if (screen) {
		SDL_DestroyWindow(screen);
	}
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}

	SDL_Quit();
}



void AStarPathFindingSample::OnExit() {
	running = false;
}