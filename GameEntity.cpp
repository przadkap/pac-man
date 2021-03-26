#include "GameEntity.h"
#include <QPointF>

void GameEntity::checkIfOnPathPoint() {
	if(pos() == QPointF(current_pathline->begin_point->x(), current_pathline->begin_point->y())) {
		current_pathpoint = current_pathline->begin_point;
	}
	else if(pos() == QPointF(current_pathline->end_point->x(), current_pathline->end_point->y())){
		current_pathpoint = current_pathline->end_point;
	}
	else {
		current_pathpoint = nullptr;
	}
}
