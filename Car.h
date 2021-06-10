#ifndef CAR_H
#define CAR_H

#include "rlutil.h"

#define CAR (1 << 8)


class Car {
    private:
    int x;
    int y = 0;
    int velocity = 0;
    int color;

    public:
    Car(){}
    Car(int x, int y, int velocity, int color){
        setX(x);
        setY(y);
        setVelocity(velocity);
        setColor(color);
    }
    
    drawCar(int posX, int posY);
    increaseVelocity();
    decreaseVelocity();
    moveLeft();
    moveRight();
    

    // Getter
    int getX(){return this->x;}
    int getY(){return this->y;}
    int getVelocity(){return this->velocity;}
    int getColor(){return this->color;}


    // Setter
    void setX(int x){this->x = x;}
    void setY(int y){this->y = y;}
    void setVelocity(int velocity){this->velocity = velocity;}
    void setColor(int color){this->color = color;}
};

Car::drawCar(int posX,int posY){
    this->x = posX;
    rlutil::setColor(this->color);
    rlutil::locate(this->x,posY);
    std::cout << " o ";
    rlutil::locate(this->x,posY+1);
    std::cout << "ooo";
    rlutil::locate(this->x,posY+2);
    std::cout << " o ";
    rlutil::locate(this->x,posY+3);
    std::cout << "ooo";

}

Car::increaseVelocity(){
	if(this->velocity >=0 && this->velocity < 5)
		this->velocity++;
	else
		this->velocity= 5;
}
Car::decreaseVelocity(){
	if(this->velocity >0 && this->velocity <= 5)
		this->velocity--;
	else
		this->velocity= 0;
}
Car::moveLeft(){
	this->x -= 4;
}
Car::moveRight(){
	this->x += 4;
}



#endif // CAR_H
