// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include "N5110.h"
#include <vector>

class Bullet {

public:
    // Constructor
    Bullet();

    void update1(int x, int y, int z);
    void update2(int x, int y, int z);
    void update3(int x, int y, int z);
    void draw(N5110 &lcd);
    void shoot1();
    void shoot2();
    void shoot3();
    int get_x1();
    int get_x2();
    int get_x3();
    int get_y1();
    int get_z1();
    int get_y2();
    int get_z2();
    int get_y3();
    int get_z3();

private:
    int x1;       
    int y1;   
    int y1_2;     
    int x2;       
    int y2;   
    int y2_2;   
    int x3;       
    int y3;   
    int y3_2;  

};

#endif 