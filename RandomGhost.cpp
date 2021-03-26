#include <RandomGhost.h>
#include <cstdlib>

RandomGhost::RandomGhost(PathLine * starting_line, PathPoint * i_flee_point, QObject * parent) {
	setParent(parent);
	move_interval = 12;

	pixmap = QPixmap("images/ghost_blue.png");
	setPixmap(pixmap);
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

	recovering = true;
	current_pathline = starting_line;
	current_pathpoint = starting_line->end_point;
	setPos(starting_line->end_point->x(), starting_line->end_point->y());
	starting_point = starting_line->end_point;
	move_direction = MOVE_UP;
	flee_point = i_flee_point;
	move_timer = new QTimer();
	connect(move_timer, SIGNAL(timeout()), this, SLOT(advance()));
	move_timer->start(move_interval);
	recovery_timer = new QTimer();
	recovery_timer->setSingleShot(true);
	connect(recovery_timer, SIGNAL(timeout()), this, SLOT(stopRecovering()));
	recovery_timer->start(5000);
	flee_timer = new QTimer();
	flee_timer->setSingleShot(true);
	connect(flee_timer, SIGNAL(timeout()), this, SLOT(stopFleeing()));
}

void RandomGhost::findTarget() {
	if(!fleeing) {
		int next_direction = rand() % 4;
		while(true) {
			if(next_direction == 0 && move_direction != MOVE_RIGHT && current_pathpoint->left) {
				current_pathline = current_pathpoint->left;
				move_direction = MOVE_LEFT;
				return;
			}
			else if(next_direction == 1 && move_direction != MOVE_LEFT && current_pathpoint->right) {
				current_pathline = current_pathpoint->right;
				move_direction = MOVE_RIGHT;
				return;
			}
			else if(next_direction == 2 && move_direction != MOVE_UP && current_pathpoint->down) {
				current_pathline = current_pathpoint->down;
				move_direction = MOVE_DOWN;
				return;
			}
			else if(next_direction == 3 && move_direction != MOVE_DOWN && current_pathpoint->up) {
				current_pathline = current_pathpoint->up;
				move_direction = MOVE_UP;
				return;
			}
			next_direction = (next_direction + 1) % 4;
		}
	}
	else {
		target_pathpoint = flee_point;
		if(current_pathpoint == flee_point) {
			target_pathpoint = flee_point->left->begin_point;
		}

		true_target = calculateNextMovement();
		changeMoveDirection();
	}
}
	
	
	
	
