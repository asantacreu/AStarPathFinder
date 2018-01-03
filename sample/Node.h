#pragma once


#include "SDL.h"
#include "Cell.h"


class Node{
	public:
		Node(int x, int y);
		Node(const Cell& cell);

		bool operator == (const Node* other) const;

		int x;
		int y;

		int f;
		int g;
		int h;

		bool IsValid();

	private:

};