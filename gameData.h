
#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdlib.h> // for srand() / rand()
#include <stdio.h>
#include "math.h"

#include "rlutil.h"
#include "Car.h"
#include "Road.h"

#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif // min

#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif // max


// Globals
Car playerCar;
Car enemyCar1;
Car enemyCar2;
Car enemyCar3;
Obstacle obstacle;
Road road;

static int counter =0;


// initiliazation of the game
void initialize(){
	
	rlutil::hidecursor();
	rlutil::saveDefaultColor();
	
	// Player Car
	playerCar.setX(2);
	playerCar.setY(MAPLENGTH - 4);
	
	enemyCar1.setX(10);
	enemyCar1.setY(MAPLENGTH - 4);
	
	enemyCar2.setX(18);
	enemyCar2.setY(MAPLENGTH - 4);
	
	enemyCar3.setX(26);
	enemyCar3.setY(MAPLENGTH - 4);
}


/// Globals
int x , y;
//int raceMapStart = MAPLENGTH -28, mapThreshold = 28;
int level = 1;
// delay for each step to draw game - otherwise it wasn't playable
void delay(int duration){
	duration =duration*1000;
	for(int i = 0; i< duration; i++){
		
	}
}

// Draws the screen
void drawInformation(){
	rlutil::locate(1, road.getMapThreshold() + 1);
	rlutil::setColor(rlutil::YELLOW);
	printf("Car Velocity: %d  y: %d \n", playerCar.getVelocity(), y);
	printf("Enemy Velocity 1: %d 2: %d 3: %d \n", enemyCar1.getVelocity(), enemyCar2.getVelocity(), enemyCar3.getVelocity());
}
// drawing each car
void drawCars(){
	if(enemyCar1.getY() <=  playerCar.getY()){
		enemyCar1.setColor(rlutil::RED);
		enemyCar1.drawCar(enemyCar1.getX(), road.getMapThreshold()-4 + (enemyCar1.getY() - playerCar.getY()));
	}
	if(enemyCar2.getY() <=  playerCar.getY()){
		enemyCar2.setColor(rlutil::RED);
		enemyCar2.drawCar(enemyCar2.getX(), road.getMapThreshold()-4 + (enemyCar2.getY() - playerCar.getY()));
	}
	if(enemyCar3.getY() <=  playerCar.getY()){
		enemyCar3.setColor(rlutil::RED);
		enemyCar3.drawCar(enemyCar3.getX(), road.getMapThreshold()-4 + (enemyCar3.getY() - playerCar.getY()));
	}
	
	playerCar.setColor(rlutil::WHITE);
	playerCar.drawCar(playerCar.getX(), road.getMapThreshold()-4);
}

void draw() {
	rlutil::cls();
	// calling draw functions
	drawInformation();
	road.drawRoad();
	drawCars();
	fflush(stdout);
}

void startGame(){
	road.gen(level);
	rlutil::setColor(2);
	printf("Welcome! Use WASD to move, ESC to quit.\n");
	rlutil::setColor(3);
	printf("When you hit a key, press and hold the w button right after it to accelerate and catch up with the opponents.\n");
	rlutil::setColor(4);
	printf("Getting stuck on obstacles slows you down. Be careful... and Good luck !\n\n");
	rlutil::setColor(6);
	rlutil::anykey("Hit any key to start.\n");
	rlutil::setColor(4);
	printf("\n");
	
}

bool detectObstacleCollision(Car &car, int carType){
	int oldX = car.getX();
	int oldY = car.getY();
	// automatic movement of the enemy cars
	if (carType == 1){
		if (road.raceMap[car.getX()][car.getY() - road.getMapThreshold() -4 ] & OBSTACLE) {
			// random movement before obstacle and sometimes car does not achieve doge the obstacle
			if(counter % 3 == 0)
				car.moveLeft();
			else if (counter % 3 == 1)
				car.moveRight();
			else
				car.decreaseVelocity();
			if (car.getX() >= MAPWIDTH || car.getX() <= 0) {car.setX(oldX); car.setY(oldY); }
			counter++;
		}
		
		if (road.raceMap[car.getX()][car.getY() - road.getMapThreshold()] & OBSTACLE) {
			car.decreaseVelocity(); 
			// if the car hits the obstacle it tries to move other sides
			if(counter % 3 == 0)
				car.moveLeft();
			else if (counter % 3 == 1)
				car.moveRight();
			else
				car.decreaseVelocity();
			if (car.getX() >= MAPWIDTH || car.getX() <= 0) {car.setX(oldX); car.setY(oldY); }
			counter++;
			return true;
		}
	// Decreasing velocity of the player car if it hits the obstacle
	} else {
		if (road.raceMap[car.getX()][car.getY() - road.getMapThreshold()] & OBSTACLE) {
			car.decreaseVelocity(); 
			return true;
		}
	}
	return false;
}

void gamePlay(){
	while (1) {
		// Input
		if (kbhit()) {
			char pressedKey = rlutil::getkey();

			int oldX = playerCar.getX();
			int oldY = playerCar.getY();
			
			if (pressedKey == 'a') {
				playerCar.moveLeft();
			} 
			else if (pressedKey == 'd') {
				playerCar.moveRight(); 
			} 		
			else if (pressedKey == 'w') { playerCar.increaseVelocity(); }
			else if (pressedKey == 's') { playerCar.decreaseVelocity(); }
			else if (pressedKey == rlutil::KEY_ESCAPE) break;
			
			
			if (playerCar.getX() >= MAPWIDTH || playerCar.getX() <= 0) {playerCar.setX(oldX); playerCar.setY(oldY); }
		}
		draw();
		// inceasing the velocity of the cars for each loop
		if(!detectObstacleCollision(enemyCar1, 1) && !counter % 3 == 0)
			enemyCar1.increaseVelocity();
		if(!detectObstacleCollision(enemyCar2, 1) && !counter % 3 == 0)
			enemyCar2.increaseVelocity();
		if(!detectObstacleCollision(enemyCar3, 1) && !counter % 3 == 0)
			enemyCar3.increaseVelocity();
		
		// focusing the cursor to the player car - if the player car is not moving, cursor waits for it
		if(playerCar.getVelocity() > 0){
			road.moveForward();
			playerCar.setY(playerCar.getY() - 1);
		}
		enemyCar1.setY(enemyCar1.getY() - 1 - (enemyCar1.getVelocity() - playerCar.getVelocity()));
		enemyCar2.setY(enemyCar2.getY() - 1 - (enemyCar2.getVelocity() - playerCar.getVelocity()));
		enemyCar3.setY(enemyCar3.getY() - 1 - (enemyCar3.getVelocity() - playerCar.getVelocity()));
		x = playerCar.getX();
		y = playerCar.getY();
		
		// Detection of the finish line passing
		if (road.raceMap[playerCar.getX()][playerCar.getY() - road.getMapThreshold()] & FINISH) { std::cout<<"You Win ! ";break; }
		else if (road.raceMap[enemyCar1.getX()][enemyCar1.getY() - road.getMapThreshold()] & FINISH) { std::cout<<"You Lost ! ";break; }
		else if (road.raceMap[enemyCar2.getX()][enemyCar2.getY() - road.getMapThreshold()] & FINISH) { std::cout<<"You Lost ! ";break; }
		else if (road.raceMap[enemyCar3.getX()][enemyCar3.getY() - road.getMapThreshold()] & FINISH) { std::cout<<"You Lost ! ";break; }
		
		detectObstacleCollision(playerCar,0);
		// delay for each movement
		delay(150000 - 10000*playerCar.getVelocity());
		counter++;
	}
}



#endif // GAMEDATA_H
