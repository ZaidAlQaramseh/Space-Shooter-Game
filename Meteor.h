#ifndef METEOR_H
#define METEOR_H

#include "mbed.h"
#include "N5110.h"

class Meteor
{

public:
    Meteor();
    void init();
    void draw(N5110 &lcd);
    void draw_collision1(N5110 &lcd);
    void draw_collision2(N5110 &lcd);
    void update();
    int random(int min, int max);
    int get_x();
    int get_y();
    int get_x2();
    int get_y2();
    int get_x3();
    int get_y3();
    void set_x(int new_x);
    void set_y(int new_y); 
    void set_x2(int new_x2);
    void set_y2(int new_y2); 
    void set_x3(int new_x2);
    void set_y3(int new_y2); 
    void set_score(int new_score);

private:

    const int METEOR[8][8]= {
	{ 0,0,1,1,1,1,0,0 },
	{ 0,1,1,1,1,1,1,0 },
	{ 1,1,0,1,1,0,1,1 },
	{ 1,1,1,0,0,1,1,1 },
	{ 1,1,1,0,0,1,1,1 },
	{ 1,1,0,1,1,0,1,1 },
	{ 0,1,1,1,1,1,1,0 },
	{ 0,0,1,1,1,1,0,0 }};

    const int collision[13][13]= {
	{ 0,0,0,1,0,0,1,0,0,1,0,0,0 },
	{ 0,1,0,0,1,0,0,1,0,0,0,1,0 },
	{ 0,0,1,0,0,0,1,0,0,1,0,0,0 },
	{ 1,0,0,1,0,1,0,1,0,0,1,0,1 },
	{ 1,0,1,1,0,0,1,0,0,0,0,1,0 },
	{ 0,1,0,0,1,0,0,0,1,0,1,0,0 },
	{ 0,0,1,0,0,0,1,0,0,0,0,0,1 },
	{ 1,0,0,0,0,1,0,0,0,1,0,1,0 },
	{ 0,0,1,0,1,0,1,0,1,0,0,0,0 },
	{ 0,1,0,1,0,1,0,0,0,0,0,1,0 },
	{ 0,0,0,0,1,0,1,0,0,1,0,0,0 },
	{ 1,0,1,0,0,0,0,1,1,0,0,1,0 },
	{ 0,1,0,0,1,0,1,0,0,1,0,0,0 }
};

    int speed;
    int x;
    int y;
    int x2;
    int y2;

    const int LIFE[6][7]= {
	{ 0,1,1,0,1,1,0 },
	{ 1,0,0,1,0,0,1 },
	{ 1,0,0,0,0,0,1 },
	{ 0,1,0,0,0,1,0 },
	{ 0,0,1,0,1,0,0 },
	{ 0,0,0,1,0,0,0 }};

    int x3;
    int y3;
 
    int score;
    bool life_out = false;

};
#endif