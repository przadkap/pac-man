#include "PathPoint.h"
#include "PathLine.h"

int PathPoint::count = 0;

PathPoint::PathPoint(int x, int y) {
	setX(x);
	setY(y);
	ordinal_no = count++;
}

// bool PathPoint::operator=(const PathPoint& p) {
// 	return((x() == p->x()) && (y() == p->y()));
// }

void PathPoint::setLeft(PathLine * line) {
	left = line;
// 	if(x() == line->begin_point->x() && y() == line->begin_point->y()) {
// 		line->end_point->setRight(line);
// 	}
// 	else {
// 		line->begin_point->setRight(line);
// 	}
}

void PathPoint::setRight(PathLine * line) {
	right = line;
// 	if(x() == line->begin_point->x() && y() == line->begin_point->y()) {
// 		line->end_point->setLeft(line);
// 	}
// 	else {
// 		line->begin_point->setLeft(line);
// 	}
}

void PathPoint::setDown(PathLine * line) {
	down = line;
// 	if(x() == line->begin_point->x() && y() == line->begin_point->y()) {
// 		line->end_point->setUp(line);
// 	}
// 	else {
// 		line->begin_point->setUp(line);
// 	}
}

void PathPoint::setUp(PathLine * line) {
	up = line;
// 	if(x() == line->begin_point->x() && y() == line->begin_point->y()) {
// 		line->end_point->setDown(line);
// 	}
// 	else {
// 		line->begin_point->setDown(line);
// 	}
}
