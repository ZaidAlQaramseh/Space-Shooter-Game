#include "N5110.h"
#include "GameEngine.h"
#include "Joystick.h"
#include <cstdio>

DigitalIn button1(PC_10);
DigitalIn button2(BUTTON1);
DigitalOut Led1(PA_15);
DigitalOut Led2(PA_14);
DigitalOut Led3(PA_13);

GameEngine::GameEngine(): _spaceship(), _bullet(), shootingFlag(false){ _lives = 3; score = 0; best_score = 0; }    

int GameEngine::update(Joystick &joystick) { 
    _spaceship.new_sprite = choose_sprite; // Update spaceship sprite
    _spaceship.update(joystick); // Update spaceship position based on joystick input
    _meteor.update(); // Update meteor position
    check_spaceship_collision(); // Check for collisions between spaceship and meteors
    update_bullets_collision(); // Check for collisions between bullets and meteors
    handleInput(); 
    Bullet_update();// Update bullet positions
    shoot();
    Light_LEDS();
    Best_score();
    return _lives;
}

void GameEngine::draw(N5110 &lcd) {
    _spaceship.draw(lcd);
    _meteor.draw(lcd);
    _bullet.draw(lcd);

    if(meteor1){_meteor.draw_collision1(lcd);
    _meteor.set_x(-100);_meteor.set_y(-100);
    meteor1 = false;}
    
    if(meteor2){_meteor.draw_collision2(lcd);
    _meteor.set_x2(-100);_meteor.set_y2(-100);
    meteor2 = false;}

    // Draw circles representing remaining bullets
    if(bullet1 + bullet2 + bullet3 == 0){
    lcd.drawCircle(36, 3, 2, FILL_TRANSPARENT);
    lcd.drawCircle(43, 3, 2, FILL_TRANSPARENT);
    lcd.drawCircle(50, 3, 2, FILL_TRANSPARENT);}

    if(bullet1 + bullet2 + bullet3 == 1){
    lcd.drawCircle(36, 3, 2, FILL_BLACK);
    lcd.drawCircle(43, 3, 2, FILL_TRANSPARENT);
    lcd.drawCircle(50, 3, 2, FILL_TRANSPARENT);}

    if(bullet1 + bullet2 + bullet3 == 2){
    lcd.drawCircle(36, 3, 2, FILL_BLACK);
    lcd.drawCircle(43, 3, 2, FILL_BLACK);
    lcd.drawCircle(50, 3, 2, FILL_TRANSPARENT);}

    if(bullet1 + bullet2 + bullet3 == 3){
    lcd.drawCircle(36, 3, 2, FILL_BLACK);
    lcd.drawCircle(43, 3, 2, FILL_BLACK);
    lcd.drawCircle(50, 3, 2, FILL_BLACK);}
}

void GameEngine::check_spaceship_collision(){
    // Get positions of meteor, spaceship, and bonus life
    int meteor_x = _meteor.get_x();
    int meteor_y = _meteor.get_y();
    int meteor_x2 = _meteor.get_x2();
    int meteor_y2 = _meteor.get_y2();
    int life_x = _meteor.get_x3();
    int life_y = _meteor.get_y3();
    int spaceship_x = _spaceship.get_x();  
    int spaceship_y = _spaceship.get_y(); 
    
    // Check collision between each meteor and spaceship
    // If collision occurs, decrease lives and update collision flags
    if (
        meteor_x < spaceship_x + 17 && 
        meteor_x + 8 > spaceship_x &&
        meteor_y < spaceship_y + 18 &&
        meteor_y + 8 > spaceship_y && !meteor1)
        {
            _lives--;
            meteor1 = true;
        }

        if (
        meteor_x2 < spaceship_x + 17 && 
        meteor_x2 + 8 > spaceship_x &&
        meteor_y2 < spaceship_y + 18 &&
        meteor_y2 + 8 > spaceship_y && !meteor2)
        {
            _lives--;
            meteor2 = true;
        }

        if (
        life_x < spaceship_x + 17 && 
        life_x + 7 > spaceship_x &&
        life_y < spaceship_y + 18 &&
        life_y + 6 > spaceship_y)
        { 
            if(_lives < 3){
            _lives++;}
            _meteor.set_x3(-100); 
            _meteor.set_y3(-100);
        }
    
}

void GameEngine::check_bullets_collision(int bullet_x, int bullet_y) {

    // Get positions of meteor and current bullet
    
    int meteor_x = _meteor.get_x();
    int meteor_y = _meteor.get_y();
    int meteor_x2 = _meteor.get_x2();
    int meteor_y2 = _meteor.get_y2();
    
    // Check collision between current bullet and each meteor
    // Collision with meteor 1
    if (bullet_x >= meteor_x && bullet_x  <= meteor_x + 7 &&
        bullet_y >= meteor_y && bullet_y <= meteor_y + 7) {
        // Bullet hit meteor 1, send meteor 1 off the screen
        score++;
        _meteor.set_score(score);
        meteor1 = true;
        if(bullet_y == _bullet.get_y1() && bullet_x == _bullet.get_x1()){
            _bullet.update1(_bullet.get_x1(), 100 , _bullet.get_z1());
        }
        if(bullet_y == _bullet.get_z1() && bullet_x == _bullet.get_x1()){
            _bullet.update1(_bullet.get_x1(), _bullet.get_y1() , 100);
        }
        if(bullet_y == _bullet.get_y2() && bullet_x == _bullet.get_x2()){
            _bullet.update2(_bullet.get_x2(), 100 , _bullet.get_z2());
        }
        if(bullet_y == _bullet.get_z2() && bullet_x == _bullet.get_x2()){
            _bullet.update2(_bullet.get_x2(), _bullet.get_y2() , 100);
        }
        if(bullet_y == _bullet.get_y3() && bullet_x == _bullet.get_x3()){
            _bullet.update3(_bullet.get_x3(), 100 , _bullet.get_z3());
        }
        if(bullet_y == _bullet.get_z3() && bullet_x == _bullet.get_x3()){
            _bullet.update3(_bullet.get_x3(), _bullet.get_y3() , 100);
        }
    }

    // Collision with meteor 2
    if (bullet_x >= meteor_x2 && bullet_x  <= meteor_x2 + 7 &&
        bullet_y >= meteor_y2 && bullet_y <= meteor_y2 + 7) {
        // Bullet hit meteor 2, send meteor 2 off the screen
        score++;
        meteor2 = true;
        _meteor.set_score(score);
        if(bullet_y == _bullet.get_y1() && bullet_x == _bullet.get_x1()){
            _bullet.update1(_bullet.get_x1(), 100 , _bullet.get_z1());
        }
        if(bullet_y == _bullet.get_z1() && bullet_x == _bullet.get_x1()){
            _bullet.update1(_bullet.get_x1(), _bullet.get_y1() , 100);
        }
        if(bullet_y == _bullet.get_y2() && bullet_x == _bullet.get_x2()){
            _bullet.update2(_bullet.get_x2(), 100 , _bullet.get_z2());
        }
        if(bullet_y == _bullet.get_z2() && bullet_x == _bullet.get_x2()){
            _bullet.update2(_bullet.get_x2(), _bullet.get_y2() , 100);
        }
        if(bullet_y == _bullet.get_y3() && bullet_x == _bullet.get_x3()){
            _bullet.update3(_bullet.get_x3(), 100 , _bullet.get_z3());
        }
        if(bullet_y == _bullet.get_z3() && bullet_x == _bullet.get_x3()){
            _bullet.update3(_bullet.get_x3(), _bullet.get_y3() , 100);
        }
    }

}

void GameEngine::update_bullets_collision(){

    check_bullets_collision(_bullet.get_x1(), _bullet.get_y1());
    check_bullets_collision(_bullet.get_x1(), _bullet.get_z1());
    check_bullets_collision(_bullet.get_x2(), _bullet.get_y2());
    check_bullets_collision(_bullet.get_x2(), _bullet.get_z2());
    check_bullets_collision(_bullet.get_x3(), _bullet.get_y3());
    check_bullets_collision(_bullet.get_x3(), _bullet.get_z3());

}

void GameEngine::handleInput() {

    // Increment bullet_count if shooting button is pressed and button state indicates a new press
    if(bullet_count >= 3){bullet_count = 0;}

    if (button1 == 1 && buttonState == 0) {

        bullet_count++;
        shootingFlag = true;
        buttonState = 1; // Update button state
     
    }
    else if(button1 == 0) {
            // Update button state
            buttonState = 0;
        }
}

void GameEngine::Bullet_update(){

    if(shootingFlag){ 
    // If shootingFlag is true, update bullet positions based on spaceship position and bullet count

        if(bullet_count == 1 && bullet1_shot == 0) { 
        _bullet.update1(_spaceship.get_x(), _spaceship.get_y(), _spaceship.get_y() + 18 );
        bullet1_shot = true;
        }
        
        if(bullet_count == 2 && bullet2_shot == 0) { 
        _bullet.update2(_spaceship.get_x(), _spaceship.get_y(), _spaceship.get_y() + 18);
        bullet2_shot = true;
        }

        if(bullet_count == 3 && bullet3_shot == 0) { 
        _bullet.update3(_spaceship.get_x(), _spaceship.get_y(), _spaceship.get_y() + 18);
        bullet3_shot = true;
        }

    }

        if(_bullet.get_x1() > 84){bullet1_shot = false;_bullet.update1(100, 100, 100);}
        if(_bullet.get_x2() > 84){bullet2_shot = false;_bullet.update2(100, 100, 100);}
        if(_bullet.get_x3() > 84){bullet3_shot = false;_bullet.update3(100, 100, 100);}

        if(bullet1_shot == false){bullet1 = 1;}else{bullet1 = 0;}
        if(bullet2_shot == false){bullet2 = 1;}else{bullet2 = 0;}
        if(bullet3_shot == false){bullet3 = 1;}else{bullet3 = 0;}

        shootingFlag = false;

}


void GameEngine::shoot(){

        if(bullet1_shot) { 
        _bullet.shoot1();}
        
        if(bullet2_shot) { 
        _bullet.shoot2();}

        if(bullet3_shot) { 
        _bullet.shoot3();}
    
    
}

int GameEngine::get_score(){
    return score;
}

void GameEngine::Light_LEDS(){ // Update LED lights based on remaining lives

    Led1 = 0;
    Led2 = 0;
    Led3 = 0;
    
    if(_lives >= 1){
        Led1 = 1;
    }
    if(_lives >= 2){
        Led2 = 1;
    }
    if(_lives == 3){
        Led3 = 1;
    }

}

int GameEngine::Best_score(){

    // Update best score if current score is higher
    if(score > best_score){best_score = score;} 

    return best_score;

}


void GameEngine::tutorial(N5110 &lcd, Joystick &joystick){
     
    init();
    
    // Loop through tutorial stages and display instructions on LCD
    while(Tutorial_menu){
    if(Move){
    lcd.clear();
    lcd.drawSprite(3, 14, 19, 18, (int*) _spaceship.SU57);
    lcd.printString("Move Joystick", 0, 0);
    lcd.refresh();
    if(joystick.get_mag() > 0){Move = false; Shoot = true;}
    }

    if(Shoot){

    lcd.clear();
    lcd.printString("Press button", 0, 0);
    lcd.printString("  to shoot", 0, 1);
    lcd.drawSprite(_spaceship.get_x(), _spaceship.get_y(), 19, 18, (int*) _spaceship.SU57);
    _bullet.draw(lcd);
    _spaceship.update(joystick);
    handleInput();
    Bullet_update();
    shoot();
    lcd.refresh();
    if(bullet3_shot){Shoot = false;Shoot2 = true;}}

    if(Shoot2){
    lcd.clear();
    lcd.printString(" You can only", 0, 1);
    lcd.printString("shoot 3 bullets", 0, 2);
    lcd.printString("  at a time!", 0, 3);
    lcd.printString("   Use them", 0, 4);
    lcd.printString("    wisely", 0, 5);
    lcd.drawCircle(36, 3, 2, FILL_BLACK);
    lcd.drawCircle(43, 3, 2, FILL_BLACK);
    lcd.drawCircle(50, 3, 2, FILL_BLACK);
    lcd.refresh();
    ThisThread::sleep_for(200ms);
    if(button1 == 1){Shoot2 = false; Health = true;}}

    if(Health){
    lcd.clear();
    lcd.printString("Shoot meteors", 0, 0);
    lcd.printString("and avoid them", 0, 1);
    lcd.printString("      Or", 0, 2);
    lcd.printString("   You die", 0, 3);
    lcd.printString("LEDS are lives", 0, 5);
    lcd.refresh();
    ThisThread::sleep_for(200ms);
    if(button1 == 1){Health = false; Meteors = true;}
    }

    if(Meteors){
    lcd.clear();
    draw(lcd);
    _spaceship.update(joystick);
    _meteor.update();
    check_spaceship_collision();
    update_bullets_collision();
    handleInput();
    Bullet_update();
    shoot();
    Light_LEDS();
    lcd.refresh();
    if(_lives == 0){Tutorial_menu = false;}
    }

    }

}

// Function to initialize game parameters for tutorial
void GameEngine::init(){
    _spaceship.x_pos = 3;
    _spaceship.y_pos = 14;
    _meteor.set_x(-100);
    _meteor.set_x2(-100);
    _meteor.set_x2(-100);
    _bullet.update1(100, 100, 100);
    _bullet.update2(100, 100, 100);
    _bullet.update3(100, 100, 100);
    bullet_count = 0;
    buttonState = 0;
    bullet1_shot = 0;
    bullet2_shot = 0;
    bullet3_shot = 0;
    bullet1 = 0;
    bullet2 = 0;
    bullet3 = 0;
    meteor1 = 0;
    meteor2 = 0;
    _lives = 3;
}



