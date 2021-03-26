#include "ChaserGhost.h"
// #include "Game.h"

ChaserGhost::ChaserGhost(PathLine * starting_line, PathPoint * i_flee_point, QObject * parent) {
	setParent(parent);
	pixmap = QPixmap("images/ghost_red.png");
	setPixmap(pixmap);
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
	move_interval = 10;
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
	recovery_timer->start(1000);
	flee_timer = new QTimer();
	flee_timer->setSingleShot(true);
	connect(flee_timer, SIGNAL(timeout()), this, SLOT(stopFleeing()));

}

void ChaserGhost::updateTarget(PathPoint * new_target_point, int new_player_move_direction) {
	if(fleeing || recovering) return;
	target_pathpoint = new_target_point;
	player_move_direction = new_player_move_direction;
}

void ChaserGhost::findTarget() {
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
	
	if(current_pathpoint->left && move_direction != MOVE_RIGHT) {
		if(target_pathpoint == current_pathpoint->left->begin_point) {
			current_pathline = current_pathpoint->left;
			move_direction = MOVE_LEFT;
			return;
		}
	}
	if(current_pathpoint->right && move_direction != MOVE_LEFT) {
		if(target_pathpoint == current_pathpoint->right->end_point) {
			current_pathline = current_pathpoint->right;
			move_direction = MOVE_RIGHT;
			return;
		}
	}
	if(current_pathpoint->down && move_direction != MOVE_UP) {
		if(target_pathpoint == current_pathpoint->down->end_point) {
			current_pathline = current_pathpoint->down;
			move_direction = MOVE_DOWN;
			return;
		}
	}
	if(current_pathpoint->up && move_direction != MOVE_DOWN) {
		if(target_pathpoint == current_pathpoint->up->begin_point) {
			current_pathline = current_pathpoint->up;
			move_direction = MOVE_UP;
			return;
		}
	}
	true_target = calculateNextMovement();
	changeMoveDirection();
}
