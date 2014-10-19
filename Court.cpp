#include "Court.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

tCourt initializeCourt() {
	tCourt newCourt;

	emptyCourt(newCourt);

	newCourt.players = resetPlayers();
	placePlayers(newCourt, PLAYER1X, PLAYER2X);

	placeBall(newCourt, INITIALXPOSITION, INITIALYPOSITION);

	srand(time(NULL));
	newCourt.ball.direction = tDir(rand() % 6);
	newCourt.ball.position.x = INITIALXPOSITION;
	newCourt.ball.position.y = INITIALYPOSITION;

	placeNet(newCourt, NETX);
	
	return newCourt;
}

//Updates the court with new information from the ball
void updateCourt(tCourt &court) {
	
	court.roundWinner = -1;

	//Collision-checking
	bool ballColPlayer = false;
	bool ballColWall = false;
	int player_part_collided = -1;

	ballCollidedPlayer(court.ball, court.players, ballColPlayer, player_part_collided);
	ballCollidedWall(court.ball, ballColWall);

	//Update positions of stuff calling their functions	
	updateBall(court.ball, ballColPlayer, player_part_collided, ballColWall);
	movePlayers(court.players);

	//Place Stuff
	emptyCourt(court);
	placePlayers(court, PLAYER1X, PLAYER2X);
	placeBall(court, court.ball.position.x, court.ball.position.y);
	placeNet(court, NETX);

	//IsThereAWinner
	isThereAWinner(court);
	
}

//Checks wether the ball has collided with a player, and returns the part
void ballCollidedPlayer(const tBall &ball, const tPlayers &players, bool &collided, int &part) {

	int diffBallToPlayer;
	int thirdOfPlayer = (PLAYER_HEIGHT / 3);

	//player 1 collision
	if (ball.position.x - PLAYER1X == 1 && ball.position.y - players.player1y >= -1 && ball.position.y - players.player1y < PLAYER_HEIGHT) {

		collided = true;
		//Calculate the part collided with
		diffBallToPlayer = (ball.position.y - players.player1y);
		if (diffBallToPlayer >= (2 * thirdOfPlayer))
			part = 3;
		else if (diffBallToPlayer >= thirdOfPlayer)
			part = 2;
		else
			part = 1;
	}

	//player 2 collision
	if (ball.position.x - PLAYER2X == -2 && ball.position.y - players.player2y >= -1 && ball.position.y - players.player2y < PLAYER_HEIGHT) {

		collided = true;
		//Calculate the part collided with
		diffBallToPlayer = (ball.position.y - players.player2y);
		if (diffBallToPlayer >= (2 * thirdOfPlayer))
			part = 3;
		else if (diffBallToPlayer >= thirdOfPlayer)
			part = 2;
		else
			part = 1;
	}
}

void ballCollidedWall(const tBall &ball, bool &collided) {
	collided = false;
	if (ball.position.y == 0)
		collided = true;
	else if (ball.position.y == COURT_HEIGHT - 2)
		collided = true;
}

int getRoundWinner(const tCourt &court) {
	return court.roundWinner;
}

//Procedures to place players, ball...
void placePlayers(tCourt &court, int player1x, int player2x) {
	for (int i = 0; i < PLAYER_HEIGHT; i++) {
		//Place player 1
		for (int j = 0; j < PLAYER_WIDTH; j++)
			court.board[court.players.player1y + i][player1x + j] = Bat;	
		//Place player 2
		for (int j = 0; j < PLAYER_WIDTH; j++)
			court.board[court.players.player2y + i][player2x + j] = Bat;
	}
}

void placeBall(tCourt &court, int ball_x, int ball_y) {
	for (int i = 0; i < BALL_HEIGHT; i++) {
		for (int j = 0; j < BALL_WIDTH; j++) {
			court.board[ball_y + i][ball_x + j] = Ball;		
		}
	}
}

void placeNet(tCourt &court, int net_x) {
	for (int i = 0; i < COURT_HEIGHT; ++i) {
		for (int j = 0; j < COURT_WIDTH; j++) {
			if (j == net_x || j == net_x + 1) {
				court.board[i][j] = Net;
			}
		}
	}
}

void emptyCourt(tCourt &court){
	for (int i = 0; i < COURT_HEIGHT; i++) {
		for (int j = 0; j < COURT_WIDTH; j++) {
			court.board[i][j] = Empty;
		}
	}
}


bool isThereAWinner(tCourt &court) {
	int i = 0;
	bool roundWin = false; // no one wins

	while ((i < COURT_HEIGHT) && (!roundWin)) {
		if ((court.board[i][0] == Ball) && (court.board[i][1] == Ball)) {
			court.roundWinner = 2;
			roundWin = true;
		}
		else if ((court.board[i][COURT_WIDTH - 1] == Ball) && (court.board[i][COURT_WIDTH] == Ball)) {
			court.roundWinner = 1;
			roundWin = true;
		}
		i++;
	}
	return roundWin;
}
