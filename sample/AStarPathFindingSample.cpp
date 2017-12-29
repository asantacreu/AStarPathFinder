
#include "stdafx.h"

#include "AStarPathFindingSample.h"

#pragma comment(linker, "/INCLUDE:_mainCRTStartup")


AStarPathFindingSample::AStarPathFindingSample() {
	screen = NULL;
}



bool AStarPathFindingSample::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	if ((screen = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL)) == NULL) {
		return false;
	}

	return true;
}



int AStarPathFindingSample::Run() {
	return 0;
}



int main(int argc, char* argv[]) {
	AStarPathFindingSample aStarPathFindingSample;

	if (aStarPathFindingSample.Init()) {
		while (true) {
			aStarPathFindingSample.Run();
		}
	}


	return 0;
}