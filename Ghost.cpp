#include "Ghost.h"
#include "Game.h"
#include "PointAndCost.h"
#include <queue>
#include <algorithm>
#include <vector>
#include <functional>

void Ghost::move() {
	if(recovering) return;
	if(pos().x() == WINDOW_WIDTH - 1 && move_direction == MOVE_RIGHT) {
		current_pathline = current_pathline->end_point->right;
		setPos(1, y());
		move_direction = MOVE_RIGHT;
		return;
	}
	else if(pos().x() == 1 && move_direction == MOVE_LEFT) {
		current_pathline = current_pathline->begin_point->left;
		setPos(WINDOW_WIDTH - 1, y());
		move_direction = MOVE_LEFT;
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
}

void Ghost::advance() {
	checkIfOnPathPoint();
	if(current_pathpoint) {
		findTarget();
	}
	move();
}

PathPoint * Ghost::calculateNextMovement() {

	std::priority_queue<point_and_cost, std::vector<point_and_cost>, std::greater<point_and_cost>> point_queue;

	int distance [current_pathpoint->count];
	bool visited [current_pathpoint->count];
	PathPoint * previous [current_pathpoint->count];
	bool first_time = true;

	for(int i = 0; i < current_pathpoint->count; ++i) {
		distance[i] = 9999;
		visited[i] = false;
		previous[i] = nullptr;
	}
	distance[current_pathpoint->ordinal_no] = 0;

	point_queue.push(point_and_cost(distance[current_pathpoint->ordinal_no], current_pathpoint));
	PathPoint * lowest_cost_point;
	while(visited[target_pathpoint->ordinal_no] == false) {

		lowest_cost_point = point_queue.top().point;
		if(visited[lowest_cost_point->ordinal_no] == true) {
			point_queue.pop();
			continue;
		}

		visited[lowest_cost_point->ordinal_no] = true;

		point_queue.pop();

		if(lowest_cost_point->left && !(first_time && move_direction == MOVE_RIGHT)) {
			if(distance[lowest_cost_point->left->begin_point->ordinal_no] >= distance[lowest_cost_point->ordinal_no] + lowest_cost_point->left->movement_cost) {
				distance[lowest_cost_point->left->begin_point->ordinal_no] = distance[lowest_cost_point->ordinal_no] + lowest_cost_point->left->movement_cost;
				point_queue.push(point_and_cost(distance[lowest_cost_point->left->begin_point->ordinal_no], lowest_cost_point->left->begin_point));
				previous[lowest_cost_point->left->begin_point->ordinal_no] = lowest_cost_point;
			}
		}
		if(lowest_cost_point->right && !(first_time && move_direction == MOVE_LEFT)) {
			if(distance[lowest_cost_point->right->end_point->ordinal_no] >= distance[lowest_cost_point->ordinal_no] + lowest_cost_point->right->movement_cost) {
				distance[lowest_cost_point->right->end_point->ordinal_no] = distance[lowest_cost_point->ordinal_no] + lowest_cost_point->right->movement_cost;
				point_queue.push(point_and_cost(distance[lowest_cost_point->right->end_point->ordinal_no], lowest_cost_point->right->end_point));
				previous[lowest_cost_point->right->end_point->ordinal_no] = lowest_cost_point;
			}
		}
		if(lowest_cost_point->down && !(first_time && move_direction == MOVE_UP)) {
			if(distance[lowest_cost_point->down->end_point->ordinal_no] >= distance[lowest_cost_point->ordinal_no] + lowest_cost_point->down->movement_cost) {
				distance[lowest_cost_point->down->end_point->ordinal_no] = distance[lowest_cost_point->ordinal_no] + lowest_cost_point->down->movement_cost;
				point_queue.push(point_and_cost(distance[lowest_cost_point->down->end_point->ordinal_no], lowest_cost_point->down->end_point));
				previous[lowest_cost_point->down->end_point->ordinal_no] = lowest_cost_point;
			}
		}
		if(lowest_cost_point->up && !(first_time && move_direction == MOVE_DOWN)) {
			if(distance[lowest_cost_point->up->begin_point->ordinal_no] >= distance[lowest_cost_point->ordinal_no] + lowest_cost_point->up->movement_cost) {
				distance[lowest_cost_point->up->begin_point->ordinal_no] = distance[lowest_cost_point->ordinal_no] + lowest_cost_point->up->movement_cost;
				point_queue.push(point_and_cost(distance[lowest_cost_point->up->begin_point->ordinal_no], lowest_cost_point->up->begin_point));
				previous[lowest_cost_point->up->begin_point->ordinal_no] = lowest_cost_point;
			}
		}
		first_time = false;
	}
	distance_to_target = distance[target_pathpoint->ordinal_no];
	PathPoint * true_target = target_pathpoint;
	while(previous[previous[true_target->ordinal_no]->ordinal_no]) {
		true_target = previous[true_target->ordinal_no];
	}

	return true_target;
}

void Ghost::changeMoveDirection() {
	if(current_pathpoint->left) {
		if(true_target == current_pathpoint->left->begin_point) {
			current_pathline = current_pathpoint->left;
			move_direction = MOVE_LEFT;
			return;
		}
	}
	if(current_pathpoint->right) {
		if(true_target == current_pathpoint->right->end_point) {
			current_pathline = current_pathpoint->right;
			move_direction = MOVE_RIGHT;
			return;
		}
	}
	if(current_pathpoint->down) {
		if(true_target == current_pathpoint->down->end_point) {
			current_pathline = current_pathpoint->down;
			move_direction = MOVE_DOWN;
			return;
		}
	}
	if(current_pathpoint->up) {
		if(true_target == current_pathpoint->up->begin_point) {
			current_pathline = current_pathpoint->up;
			move_direction = MOVE_UP;
			return;
		}
	}
}

void Ghost::setFleeing() {
	fleeing = true;
	setPixmap(QPixmap("images/ghost_scared.png"));
	target_pathpoint = flee_point;
	flee_timer->start(10000);
	move_timer->start(move_interval * 1.5);
}

void Ghost::checkPlayerCollision(QRectF pac_rect) {
	if(pac_rect.intersects(QRectF(pos().x(), pos().y(), GHOST_SIZE, GHOST_SIZE))) {
		if(recovering) return;
		else if(fleeing) {
			emit ghostEaten();
			backToLair();
		}
		else {
			emit playerDamaged("YOU LOST!!!");
		}
	}
}

void Ghost::backToLair() {
	recovering = true;
	setPos(starting_point->x(), starting_point->y());
	current_pathline = starting_point->up;
	move_direction = MOVE_UP;
	recovery_timer->start(3000);
}

void Ghost::stopRecovering() {
	recovering = false;
	emit requestNewTarget();
}

void Ghost::stopFleeing() {
	setPixmap(pixmap);
	fleeing = false;
	move_timer->start(move_interval);
	emit requestNewTarget();
}
