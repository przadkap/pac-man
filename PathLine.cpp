#include "PathLine.h"
#include "PathPoint.h"

PathLine::PathLine(PathPoint* begin, PathPoint* end, int direction, int length) {
	setPoints(QPoint(begin->x(), begin->y()), QPoint(end->x(), end->y()));
	movement_cost = length;
	begin_point = begin;
	end_point = end;
	if(direction == HORIZONTAL) {
		begin->setRight(this);
		end->setLeft(this);
	}
	else {
		begin->setDown(this);
		end->setUp(this);
	}
	line_to_draw = new QGraphicsLineItem(begin->x(), begin->y(), end->x(), end->y());
}
