#include <cstdlib>
#include <stdlib.h>

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player{
    private:
    public:

    int x;
    int y;
    int health;
    int direction;

    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();
    void renderPlayer();
    void attackPlayer();

    Player(){
        x = 0;
        y = 0;
        direction = 0;
    }

};

#endif // PLAYER_H_INCLUDED
