#include "player.h"

void Player::moveDown(){
    if (y < 7){y++;}
    else{y = 7;}
    direction = 2;
}

void Player::moveUp(){
    if (y > 0){y--;}
    else{y = 0;}
    direction = 0;
}

void Player::moveLeft(){
    if (x > 0){x--;}
    else{x = 0;}
    direction = 3;
}

void Player::moveRight(){
    if (x < 7){x++;}
    else{x = 7;}
    direction = 1;
}

void Player::attackPlayer(){

}

