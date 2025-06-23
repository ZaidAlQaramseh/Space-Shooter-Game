#include "Bullet.h"
#include "N5110.h"
#include "Spaceship.h"
#include <vector>


// Constructor
Bullet::Bullet() : x1(100), y1(100), x2(100), y2(100), x3(100), y3(100) {}


// Method to update the bullet's position
void Bullet::update1(int x, int y, int z) {

    x1 = x;
    y1 = y;
    y1_2 = z;
}

void Bullet::update2(int x, int y, int z) {

    x2 = x;
    y2 = y;
    y2_2 = z;
}

void Bullet::update3(int x, int y, int z) {

    x3 = x;
    y3 = y;
    y3_2 = z;

}

int Bullet::get_x1(){
    return x1;
}

int Bullet::get_x2(){
    return x2;
}

int Bullet::get_x3(){
    return x3;
}

int Bullet::get_y1(){
    return y1;
}

int Bullet::get_y2(){
    return y2;
}

int Bullet::get_y3(){
    return y3;
}

int Bullet::get_z1(){
    return y1_2;
}

int Bullet::get_z2(){
    return y2_2;
}

int Bullet::get_z3(){
    return y3_2;
}

// Method to draw each bullet
void Bullet::draw(N5110 &lcd) {

    lcd.drawRect(x1 + 10, y1, 2, 1, FILL_BLACK);
    lcd.drawRect(x1+ 10, y1_2, 2, 1, FILL_BLACK);

    lcd.drawRect(x2 + 10, y2, 2, 1, FILL_BLACK);
    lcd.drawRect(x2+ 10, y2_2, 2, 1, FILL_BLACK);

    lcd.drawRect(x3 + 10, y3, 2, 1, FILL_BLACK);
    lcd.drawRect(x3+ 10, y3_2, 2, 1, FILL_BLACK);
}

void Bullet::shoot1(){
    x1++;
}

void Bullet::shoot2(){
    x2++;
}

void Bullet::shoot3(){
    x3++;
}
    

