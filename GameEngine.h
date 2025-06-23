#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Joystick.h"
#include "mbed.h"
#include "N5110.h"
#include "Spaceship.h"
#include "Meteor.h"
#include "Bullet.h"

class GameEngine {
    public:
        GameEngine();
        int update(Joystick &joystick);
        void draw(N5110 &lcd);
        void check_spaceship_collision();
        void check_bullets_collision(int bullet_x, int bullet_y);
        void update_bullets_collision();
        void handleInput();
        void Bullet_update();
        void shoot();
        void tutorial(N5110 &lcd, Joystick &joystick);
        int get_score();
        void Light_LEDS();
        int Best_score();
        void init();
        bool Tutorial_menu;
        bool Move = true;
        bool Shoot = false;
        bool Shoot2 = false;
        bool Meteors = false;
        bool Health = false;
        int choose_sprite = 1;
        int _lives;
        int score;

    private:
        Spaceship _spaceship;
        Meteor _meteor;
        Bullet _bullet;
        bool shootingFlag;
        int bullet_count = 0;
        int buttonState = 0;
        bool bullet1_shot = 0;
        bool bullet2_shot = 0;
        bool bullet3_shot = 0;
        int bullet1 = 0;
        int bullet2 = 0;
        int bullet3 = 0;
        bool meteor1 = 0;
        bool meteor2 = 0;
        int best_score;
};

#endif