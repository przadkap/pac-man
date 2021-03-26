#include "Player.h"
#include <QKeyEvent>
#include <QPixmap>

Player::Player(PathLine * starting_line, QObject * parent) {
	setParent(parent);
	move_interval = 9;
	setPixmap(QPixmap("images/pacman_right.png"));
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
	current_pathline = starting_line;
	current_pathpoint = starting_line->begin_point;
	setPos(starting_line->begin_point->x(), starting_line->begin_point->y());
	move_direction = MOVE_RIGHT;
	next_move_direction = MOVE_RIGHT;
	move_timer = new QTimer();
	connect(move_timer, SIGNAL(timeout()), this, SLOT(advance()));
	move_timer->start(move_interval);
	emit previousTargetChanged(current_pathpoint, move_direction);
	emit nextTargetChanged(starting_line->end_point, move_direction);
}

void Player::setNewTarget() {
	if(move_direction == MOVE_UP || move_direction == MOVE_LEFT) {
		emit previousTargetChanged(current_pathline->end_point, move_direction);
		emit nextTargetChanged(current_pathline->begin_point, move_direction);
	}
	else {
		emit previousTargetChanged(current_pathline->begin_point, move_direction);
		emit nextTargetChanged(current_pathline->end_point, move_direction);
	}
}

void Player::setDirection(QKeyEvent *event) {
	if(event->key() == Qt::Key_Left) {
		stopped = false;
		if(move_direction == MOVE_RIGHT) {
			move_direction = MOVE_LEFT;
			setNewTarget();
			setPixmap(QPixmap("images/pacman_left.png"));
		}
		next_move_direction = MOVE_LEFT;
	}
	if(event->key() == Qt::Key_Right) {
		stopped = false;
		if(move_direction == MOVE_LEFT) {
			move_direction = MOVE_RIGHT;
			setNewTarget();
			setPixmap(QPixmap("images/pacman_right.png"));
		}
		next_move_direction = MOVE_RIGHT;
	}
	if(event->key() == Qt::Key_Up) {
		stopped = false;
		if(move_direction == MOVE_DOWN) {
			move_direction = MOVE_UP;
			setNewTarget();
			setPixmap(QPixmap("images/pacman_up.png"));
		}
		next_move_direction = MOVE_UP;
	}
	if(event->key() == Qt::Key_Down) {
		stopped = false;
		if(move_direction == MOVE_UP) {
			move_direction = MOVE_DOWN;
			setNewTarget();
			setPixmap(QPixmap("images/pacman_down.png"));
		}
		next_move_direction = MOVE_DOWN;
	}
}

void Player::advance() {
	if(stopped) {
		emit positionChanged(QRectF(current_pathpoint->x(), current_pathpoint->y(), PLAYER_SIZE, PLAYER_SIZE));
		return;
	}
	checkIfOnPathPoint();
	if(current_pathpoint) {
		if(next_move_direction == MOVE_LEFT) {
			if(current_pathpoint->left) {
				current_pathline = current_pathpoint->left;
				move_direction = next_move_direction;
				setNewTarget();
				setPixmap(QPixmap("images/pacman_left.png"));
			}
			else {
				moveAlongCurrentDirection();
			}
		}
		else if(next_move_direction == MOVE_RIGHT) {
			if(current_pathpoint->right) {
				current_pathline = current_pathpoint->right;
				move_direction = next_move_direction;
				setNewTarget();
				setPixmap(QPixmap("images/pacman_right.png"));
			}
			else {
				moveAlongCurrentDirection();
			}
		}
		else if(next_move_direction == MOVE_DOWN) {
			if(current_pathpoint->down) {
				current_pathline = current_pathpoint->down;
				move_direction = next_move_direction;
				setNewTarget();
				setPixmap(QPixmap("images/pacman_down.png"));
			}
			else {
				moveAlongCurrentDirection();
			}
		}
		else if(next_move_direction == MOVE_UP) {
			if(current_pathpoint->up) {
				current_pathline = current_pathpoint->up;
				move_direction = next_move_direction;
				setNewTarget();
				setPixmap(QPixmap("images/pacman_up.png"));
			}
			else {
				moveAlongCurrentDirection();
			}
		}
	}
	move();
}

void Player::moveAlongCurrentDirection() {
	if(move_direction == MOVE_LEFT) {
		if(current_pathpoint->left) {
			current_pathline = current_pathpoint->left;
			setNewTarget();
		}
		else stop();
	}
	else if(move_direction == MOVE_RIGHT) {
		if(current_pathpoint->right) {
			current_pathline = current_pathpoint->right;
			setNewTarget();
		}
		else stop();
	}
	else if(move_direction == MOVE_DOWN) {
		if(current_pathpoint->down) {
			current_pathline = current_pathpoint->down;
			setNewTarget();
		}
		else stop();
	}
	else if(move_direction == MOVE_UP) {
		if(current_pathpoint->up) {
			current_pathline = current_pathpoint->up;
			setNewTarget();
		}
		else stop();
	}
}

void Player::move() {
	if(stopped) {
		return;
	}
	if(x() == WINDOW_WIDTH - 1 && move_direction == MOVE_RIGHT) {
		setPos(1, y());
		current_pathline = current_pathline->end_point->right;
		current_pathpoint = current_pathline->begin_point;
		emit previousTargetChanged(current_pathpoint, move_direction);
		emit nextTargetChanged(current_pathpoint, move_direction);
		emit positionChanged(QRectF(x() + 5, y() + 5, PLAYER_SIZE - 5, PLAYER_SIZE - 5));
		return;
	}
	if(x() == 1 && move_direction == MOVE_LEFT) {
		setPos(WINDOW_WIDTH - 1, y());
		current_pathline = current_pathline->begin_point->left;
		current_pathpoint = current_pathline->end_point;
		emit previousTargetChanged(current_pathpoint, move_direction);
		emit nextTargetChanged(current_pathpoint, move_direction);
		emit positionChanged(QRectF(x() + 5, y() + 5, PLAYER_SIZE - 5, PLAYER_SIZE - 5));
		return;
	}

	if(move_direction == MOVE_LEFT) {
		setPos(x() - STEP, y());
	}
	else if(move_direction == MOVE_RIGHT) {
		setPos(x() + STEP, y());
	}
	else if(move_direction == MOVE_DOWN) {
		setPos(x(), y() + STEP);
	}
	else if(move_direction == MOVE_UP) {
		setPos(x(), y() - STEP);
	}
	emit positionChanged(QRectF(x() + 5, y() + 5, PLAYER_SIZE - 5, PLAYER_SIZE - 5));
}

void Player::stop() {
	stopped = true;
}

void Player::keyPressEvent(QKeyEvent *event) {
	setDirection(event);
}
