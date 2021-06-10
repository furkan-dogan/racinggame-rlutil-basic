#ifndef ROAD_H
#define ROAD_H

#include "rlutil.h"
#include "Obstacle.h"

#define MAPLENGTH 280
#define MAPWIDTH 37

/// Tiles

#define WALL 1
#define STRIPE (1 << 1)
#define OBSTACLE (1 << 2)
#define FINISH (1 << 4)

class Road {
	// road width, height decleration
    private:
    static const int width = MAPWIDTH;
    static const int length = MAPLENGTH;
    int color;
	int raceMapStart = this->length - 28, mapThreshold = 28;
	Obstacle obstacle;

    public:
    int raceMap[width][length];
    Road(){}
    // generation and drawing of the road
    drawRoad();
    gen(int seed);

    // Getter
    int getWidth(){return this->width;}
    int getLength(){return this->length;}
    int getColor(){return this->color;}
    int getMapThreshold(){ return this->mapThreshold; }
    


    // Setter
    void setColor(int color){this->color = color;}
    
	// Facilitator
    void moveForward(){ this->raceMapStart--;}
};

Road::gen(int seed) {
	srand(seed);
	for (int j = 0; j < this->length; j++) {
		for (int i = 0; i < this->width; i++) {
			if (i == 0 || i == this->width-1 ){
				// randomly adding obstacles
				if (rand() % 40 == 0) {
						obstacle.drawObstacle(raceMap, i + 1, j);
				}
				raceMap[i][j] = 1;	
			}
			else if (i % 4 == 0) {
				// addition of stripes
				raceMap[i][j] = STRIPE;
				if (rand() % 40 == 0) {
					obstacle.drawObstacle(raceMap, i + 1, j);
				}
			}
			else{
				//raceMap[i][j] = 0;
			}
			if( j == 0){
				// finish line
				raceMap[i][j] = FINISH;
			}
			
		}
	}
}

Road::drawRoad(){
	rlutil::locate(1, 1);
	
	for (int j = raceMapStart - mapThreshold ; j < raceMapStart  ; j++) {
		for (int i = 0; i < this->width; i++) {
			if (0);
			// drawing road from the race map according to the values assigned to that element of the raceMap
			else if (raceMap[i][j] == 0) { rlutil::setColor(rlutil::BLUE); printf(" "); }
			else if (raceMap[i][j] & WALL) { rlutil::setColor(rlutil::CYAN); printf("#"); }
			else if (raceMap[i][j] & STRIPE) { rlutil::setColor(rlutil::YELLOW); printf("|"); }
			else if (raceMap[i][j] & OBSTACLE) { rlutil::setColor(rlutil::BLUE); printf("o"); }
			else if (raceMap[i][j] & FINISH) { rlutil::setColor(rlutil::GREEN); printf("="); }
		
		}
		printf("\n");
	}
}

#endif // ROAD_H
