
#include "stdafx.h"


#include "AStarPathFindingSample.h"


#include "Defines.h"
#include "stdio.h"
#include "Node.h"
#include "math.h"


AStarPathFindingSample::AStarPathFindingSample() 
	: startCell(STARTCELL_DEFAULT_X, STARTCELL_DEFAULT_Y, 0, 255, 0, SDL_ALPHA_OPAQUE),
	endCell(ENDCELL_DEFAULT_X, ENDCELL_DEFAULT_Y, 255, 0, 0, SDL_ALPHA_OPAQUE)
{
	running = true;
	startSearch = false;
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
		SDL_CreateWindowAndRenderer(GRID_WIDTH, GRID_HEIGHT, 0, &screen, &renderer);

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
		case SDL_KEYDOWN:
			printf("Key press detected\n");
			break;

		case SDL_KEYUP:
			printf("Key release detected\n");
			switch (event->key.keysym.sym) {
				case SDLK_s:
					if (!startSearch) {
						startSearch = true;
					}
					break;

				case SDLK_c:
					ClearGrid();
					break;

				default:
					break;
			}
			break;

		case SDL_QUIT:
			OnExit();
			break;

		default:
			break;
	}
}



void AStarPathFindingSample::ClearGrid() {
	open.clear();
	closed.clear();
}



void AStarPathFindingSample::OnLoop() {
	if (startSearch) {
		startSearch = false;

		Node goal(endCell);

		//1.  Initialize the open list
		open.clear();

		//2.  Initialize the closed list
		// put the starting node on the open 
		// list(you can leave its f at zero)
		closed.clear();
		open.push_back(Node(startCell));

		//3.  while the open list is not empty
		bool goalFound = false;
		while (!goalFound && !open.empty()) {
			// a) find the node with the least f on
			// the open list, call it "q"
			Node q = GetLeastFNode(open);

			// b) pop q off the open list
			std::vector<Node>::const_iterator nodeIt = FindNode(q, open);
			if (nodeIt != open.end()) {
				open.erase(nodeIt);
			}

			//c) generate q's 4 successors and set their 
			//parents to q
			std::vector<Node> successors;
			GenerateSuccessors(q, successors);

			//d) for each successor
			for (auto it = successors.begin(); it != successors.end(); it++) {
				//i) if successor is the goal, stop search
				Node* successor = &(*it);
				if (goal == successor) {
					goalFound = true;
					break;
				}

				successor->g = q.g + 1;

				int x = (it->x - goal.x);
				int y = (it->y - goal.y);
				successor->h = (abs(x) + abs(y));

				successor->f = (successor->g + successor->h);

				std::vector<Node>::const_iterator nodeClosedIt = FindNode(*successor, closed);
				if (nodeClosedIt == closed.end()) {
					std::vector<Node>::iterator nodeOpenIt = FindNode(*successor, open);
					if (nodeOpenIt == open.end()) {
						open.push_back(*successor);
					}else{
						if (successor->f < nodeOpenIt->f) {
							nodeOpenIt->f = successor->f;
						}
					}
				}
			}

			//e) push q on the closed list
			closed.push_back(q);

		}



	}
}



Node AStarPathFindingSample::GetLeastFNode(std::vector<Node>& vector) {
	Node leastFNode = Node(*vector.begin());

	int leastF = leastFNode.f;

	for (auto it = vector.begin(); it != vector.end(); it++) {
		if (it->f < leastF) {
			leastF = it->f;
			leastFNode = Node(*it);
		}
	}

	return leastFNode;
}



std::vector<Node>::iterator AStarPathFindingSample::FindNode(const Node& nodeToSearch, std::vector<Node>& list) {
	std::vector<Node>::iterator it = list.begin();

	for (it = list.begin(); it != list.end(); it++) {
		const Node* node = &(*it);
		if (nodeToSearch == node) {
			break;
		}
	}

	return it;
}



void AStarPathFindingSample::GenerateSuccessors(Node& node, std::vector<Node>& successors) {
	Node northSuccessor(node.x, node.y - 1);
	if (northSuccessor.IsValid()) {
		successors.push_back(northSuccessor);
	}

	Node southSuccessor(node.x, node.y + 1);
	if (southSuccessor.IsValid()) {
		successors.push_back(southSuccessor);
	}

	Node westSuccessor(node.x - 1, node.y);
	if (westSuccessor.IsValid()) {
		successors.push_back(westSuccessor);
	}

	Node eastSuccessor(node.x + 1, node.y);
	if (eastSuccessor.IsValid()) {
		successors.push_back(eastSuccessor);
	}
}



void AStarPathFindingSample::OnPaint() {
	PaintBackground();

	PaintGrid();

	if (!open.empty()) {
		for (auto it = open.begin(); it != open.end(); it++) {
			Cell cell(it->x, it->y, 0, 0, 255, SDL_ALPHA_OPAQUE);
			cell.Paint(renderer);
		}
	}

	if (!closed.empty()) {
		for (auto it = closed.begin(); it != closed.end(); it++) {
			Cell cell(it->x, it->y, 255, 255, 0, SDL_ALPHA_OPAQUE);
			cell.Paint(renderer);
		}
	}

	startCell.Paint(renderer);
	endCell.Paint(renderer);

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