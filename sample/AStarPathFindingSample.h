#pragma once


#include "SDL.h"


#include <vector>
#include "Cell.h"
#include "Node.h"


class AStarPathFindingSample {
	public:
		AStarPathFindingSample();

		int Run();

	private:
		bool running;
		bool startSearch;
		SDL_Window* screen;
		SDL_Renderer* renderer;

		Cell startCell;
		Cell endCell;

		std::vector<Node> open;
		std::vector<Node> closed;

		bool OnInit();
		void OnExecute();
		void OnEvent(SDL_Event* event);
		void ClearGrid();
		void OnLoop();
		Node GetLeastFNode(std::vector<Node>& vector);
		std::vector<Node>::iterator FindNode(const Node& q, std::vector<Node>& open);
		void GenerateSuccessors(Node& node, std::vector<Node>& successors);
		void OnPaint();
		void PaintBackground();
		void PaintGrid();
		void OnCleanUp();
		void OnExit();

};