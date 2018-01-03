
#include "stdafx.h"

#include "Node.h"

#include "Defines.h"



Node::Node(int x, int y) {
	this->x = x;
	this->y = y;

	this->f = 0;
	this->g = 0;
	this->h = 0;
}



Node::Node(const Cell& cell) {
	this->x = cell.GetX();
	this->y = cell.GetY();

	this->f = 0;
	this->g = 0;
	this->h = 0;
}



bool Node::operator == (const Node* other) const {
	return (this->x == other->x && this->y == other->y);
}



bool Node::IsValid() {
	bool xValid = (x >= 0 && x < GRID_COLUMNS);
	bool yValid = (y >= 0 && y < GRID_ROWS);
	return (xValid && yValid);
}