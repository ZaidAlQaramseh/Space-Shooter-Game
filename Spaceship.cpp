// spaceship.cpp
#include "Spaceship.h"
#include "Joystick.h"


Spaceship::Spaceship() 
: x_pos(3), y_pos(14), sprite() {new_sprite = 1;}

void Spaceship::draw(N5110 &lcd) { 
    lcd.drawSprite(x_pos, y_pos, 19, 18, (int*) sprite);
}

void Spaceship::update(Joystick &joystick) {

        if(joystick.get_direction() == N){
           y_pos--;

        }else if(joystick.get_direction() == S){
            y_pos++;;

        }else if(joystick.get_direction() == E){
            x_pos++;

        }else if(joystick.get_direction() == W){
            x_pos--;

        }else if(joystick.get_direction() == NE){
            y_pos--;
            x_pos++;

        }else if(joystick.get_direction() == NW){
            y_pos--;
            x_pos--;

        }else if(joystick.get_direction() == SE){
            y_pos++;;
            x_pos++;

        }else if(joystick.get_direction() == SW){
            y_pos++;
            x_pos--;
        }

    boundary(x_pos, y_pos);

        if(new_sprite == 1){

        if(joystick.get_mag()){
        sprite = (int*) SU57_2;
        } else{ sprite = (int*) SU57;}
        
        }

        if(new_sprite == 2 ){

        if(joystick.get_mag()){
        sprite = (int*) F35_2;
        } else{ sprite = (int*) F35;}

        }


}


void Spaceship::boundary(int x, int y){

    if (x < 0 ){        //ensure that the point doesnt pass beyond the left hand side of the screen
        x_pos = 0;
    }else if (x > 25){  //ensure that the point doesnt pass beyond the right hand side of the screen-
        x_pos = 25;
    }

    if(y < 0){          //ensure that the point doesnt pass beyond the top of the screen
        y_pos = 0;
    }else if(y > 29){   //ensure that the point doesnt pass beyond the bottom of the screen
        y_pos = 29;
    }
}

int Spaceship::get_x() { return x_pos; }
int Spaceship::get_y() { return y_pos; }




