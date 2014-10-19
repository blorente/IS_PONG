#include "Ball.h"

void updateBall(tBall &ball, bool collision_player, int collisionZonePlayer, bool collision_wall) {
	updateBallDirection(ball, collision_player, collisionZonePlayer, collision_wall);
	updateBallPosition(ball);
}

void updateBallPosition(tBall &ball) {
	switch (ball.direction) {
		case up_right: {
			ball.position.x += 1;
			ball.position.y += 1;
			break;
		}
		case mid_right: {
			ball.position.x += 1;
			break;
		}
		case down_right: {
			ball.position.x += 1;
			ball.position.y -= 1;
			break;
		}
		case up_left: {
			ball.position.x -= 1;
			ball.position.y += 1;
			break;
		}
		case mid_left: {
			ball.position.x -= 1;
			break;
		}
		case down_left: {
			ball.position.x -= 1;
			ball.position.y -= 1;
			break;
		}
	}
}

void updateBallDirection(tBall &ball, bool collision_player, int collisionZonePlayer, bool collision_wall) {
	if (collision_player && collision_wall) {
		if ((ball.direction == up_right) && (collisionZonePlayer == 1))
			ball.direction = down_left;
		else if ((ball.direction == up_left) && (collisionZonePlayer == 1))
			ball.direction = down_right;
		else if ((ball.direction == down_right) && (collisionZonePlayer == 3))
			ball.direction = up_left;
		else if ((ball.direction == down_left) && (collisionZonePlayer == 3))
			ball.direction = up_right;
	}

	else if (!collision_wall && collision_player) {
		if (collisionZonePlayer == 1) {
			if (ball.direction == up_left)
				ball.direction = up_right;
			else if (ball.direction == mid_left)
				ball.direction = up_right;
			else if (ball.direction == down_left)
				ball.direction = mid_right;
			else if (ball.direction == up_right)
				ball.direction = up_left;
			else if (ball.direction == mid_right)
				ball.direction = up_left;
			else if (ball.direction == down_right)
				ball.direction = mid_left;
		}

		else if (collisionZonePlayer == 2) {
			if (ball.direction == up_left)
				ball.direction = up_right;
			else if (ball.direction == mid_left)
				ball.direction = mid_right;
			else if (ball.direction == down_left)
				ball.direction = down_right;
			else if (ball.direction == up_right)
				ball.direction = up_left;
			else if (ball.direction == mid_right)
				ball.direction = mid_left;
			else if (ball.direction == down_right)
				ball.direction = down_left;
		}

		else if (collisionZonePlayer == 3) {
			if (ball.direction == up_left)
				ball.direction = mid_right;
			else if (ball.direction == mid_left)
				ball.direction = down_right;
			else if (ball.direction == down_left)
				ball.direction = down_right;
			else if (ball.direction == up_right)
				ball.direction = mid_left;
			else if (ball.direction == mid_right)
				ball.direction = down_left;
			else if (ball.direction == down_right)
				ball.direction = down_left;
		}
	}

	else if (collision_wall && !collision_player) {
		if (ball.direction == up_right)
			ball.direction = down_right;
		else if (ball.direction == up_left)
			ball.direction = down_left;
		else if (ball.direction == down_right)
			ball.direction = up_right;
		else if (ball.direction == down_left)
			ball.direction = up_left;
	}
}
