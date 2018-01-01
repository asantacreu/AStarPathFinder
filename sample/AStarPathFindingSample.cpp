
#include "stdafx.h"

#include "AStarPathFindingSample.h"

#pragma comment(linker, "/INCLUDE:_mainCRTStartup")



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
		screen = SDL_CreateWindow("AStarPathFindingSample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
		if (screen != NULL) {
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

}



void AStarPathFindingSample::OnCleanUp() {
	SDL_DestroyWindow(screen);

	SDL_Quit();
}



void AStarPathFindingSample::OnExit() {
	running = false;
}