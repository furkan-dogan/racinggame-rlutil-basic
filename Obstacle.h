#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameData.h"

#define OBSTACLE (1 << 2)

class Obstacle {
    private:
    // location of the obstacle
    int x;
    int y;
    int color;

    public:
    // Constructors
    Obstacle(){}
    Obstacle(int x, int y, int color){
        setX(x);
        setY(y);
        setColor(color);
    }
    // drawing obstacle between two stripe
    drawObstacle(int raceMap[37][280], int posX, int posY);

    // Getter
    int getX(){return this->x;}
    int getY(){return this->y;}
    int getColor(){return this->color;}


    // Setter
    void setX(int x){this->x = x;}
    void setY(int y){this->y = y;}
    void setColor(int color){this->color = color;}
};

// drawing obstacle
Obstacle::drawObstacle(int raceMap[37][280], int posX, int posY){
	
	for(int j = posY; j<posY+3; j++){
		for(int i = posX; i< posX+3;i++){
			raceMap[i][j] = OBSTACLE;
		}
	}
}

#endif // OBSTACLE_H
