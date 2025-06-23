#include "Meteor.h"
#include "N5110.h"
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 84;
const int SCREEN_HEIGHT = 48;

Meteor::Meteor() {     
    
    // Initialize the meteor's position randomly within the screen bounds
    x = SCREEN_WIDTH;
    y = random(0 + 8, SCREEN_HEIGHT - 8); // Ensure the whole meteor is visible

    // Initialize the speed of the meteor
    speed = 1;

    // Initialize the position and speed of the second meteor
    x2 = SCREEN_WIDTH; 
    y2 = random(0 + 8, SCREEN_HEIGHT - 8); // Ensure the whole meteor is visible

    x3 = -100;
    y3 = -100;

}


void Meteor::draw(N5110 &lcd) {
    
    lcd.drawSprite(x, y, 8, 8, (int*) METEOR);

    lcd.drawSprite(x2, y2, 8, 8, (int*) METEOR);

    lcd.drawSprite(x3, y3, 6, 7, (int*) LIFE );
}

void Meteor::draw_collision1(N5110 &lcd) {

     lcd.drawSprite(x, y, 13, 13, (int*) collision);
}

void Meteor::draw_collision2(N5110 &lcd) {

     lcd.drawSprite(x2, y2, 13, 13, (int*) collision);
}

void Meteor::update(){
   
    x -= speed;
    x2 -= speed;
    x3 -=speed;

    //Reset the meteor's position if it moves out of the screen
    if (x < 0) {
        x = SCREEN_WIDTH;
        y = random(0 + 8, SCREEN_HEIGHT - 8); // Ensure the whole meteor is visible
    }

    // Reset the position of the second meteor if it moves out of the screen
    if (x2 < 0 & x < 30) {
        x2 = SCREEN_WIDTH;
        y2 = random(0 + 8, SCREEN_HEIGHT - 8); // Ensure the whole meteor is visible
    }

    if(score % 11 == 0){life_out = false;}
    
    if (x3 < 0 && score % 10 == 0 && score > 0 && !life_out) {
        x3 = SCREEN_WIDTH;
        y3 = random(0 + 6, SCREEN_HEIGHT - 6); 
        life_out = true;
    }

}

// Function to generate a random number within a range
int Meteor::random(int min, int max) {
    static bool initialized = false;
    if (!initialized) {
        std::srand(std::time(nullptr));
        initialized = true;
    }
    return min + std::rand() % (max - min + 1);
}

int Meteor::get_x() { return x; }
int Meteor::get_y() { return y; }
int Meteor::get_x2() { return x2; }
int Meteor::get_y2() { return y2; }
int Meteor::get_x3() { return x3; }
int Meteor::get_y3() { return y3; }

void Meteor::set_x(int new_x) {x = new_x;}
void Meteor::set_y(int new_y) {y = new_y;}
void Meteor::set_x2(int new_x2) {x2 = new_x2;}
void Meteor::set_y2(int new_y2) {y2 = new_y2;}
void Meteor::set_x3(int new_x3) {x3 = new_x3;}
void Meteor::set_y3(int new_y3) {y3 = new_y3;}

void Meteor::set_score(int new_score) {score = new_score;}


