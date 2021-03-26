#include "ScaredGhost.h"
#include "Game.h"



ScaredGhost::ScaredGhost(PathLine * starting_line, PathPoint * i_flee_point, QObject * parent) {

	setParent(parent);
	pixmap = QPixmap("images/ghost_orange.png");
	setPixmap(pixmap);
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
	move_interval = 14;
	recovering = true;
	current_pathline = starting_line;
	current_pathpoint = nullptr;
	setPos(starting_line->end_point->x(), starting_line->end_point->y());
	starting_point = starting_line->end_point;
	move_direction = MOVE_UP;
	player_move_direction = MOVE_RIGHT;
	target_pathpoint = starting_line->begin_point;
	flee_point = i_flee_point;
	move_timer = new QTimer();
	connect(move_timer, SIGNAL(timeout()), this, SLOT(advance()));
	move_timer->start(move_interval);
	recovery_timer = new QTimer();
	recovery_timer->setSingleShot(true);
	connect(recovery_timer, SIGNAL(timeout()), this, SLOT(stopRecovering()));
	recovery_timer->start(7000);
	flee_timer = new QTimer();
	flee_timer->setSingleShot(true);
	connect(flee_timer, SIGNAL(timeout()), this, SLOT(stopFleeing()));
}

void ScaredGhost::updateTarget(PathPoint * new_target_point, int new_player_move_direction) {
	if(fleeing || recovering) return;
	target_pathpoint = new_target_point;
	player_move_direction = new_player_move_direction;
}

void ScaredGhost::findTarget() {
	if(fleeing) {
		target_pathpoint = flee_point;
	}
		
	if(current_pathpoint == target_pathpoint) {
		if(!fleeing) {
			if(player_move_direction == MOVE_DOWN) {
				target_pathpoint = current_pathpoint->up->begin_point;
			}
			else if(player_move_direction == MOVE_UP) {
				target_pathpoint = current_pathpoint->down->end_point;
			}
			else if(player_move_direction == MOVE_LEFT) {
				target_pathpoint = current_pathpoint->right->end_point;
			}
			else if(player_move_direction == MOVE_RIGHT) {
				target_pathpoint = current_pathpoint->left->begin_point;
			}
		}
		else {
			target_pathpoint = flee_point->right->end_point;
		}
	}

	true_target = calculateNextMovement();

	if(distance_to_target <= 40) {
		target_pathpoint = flee_point;
		true_target = calculateNextMovement();
	}
	changeMoveDirection();

}
