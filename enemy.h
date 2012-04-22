#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

class Enemy{
    private:
    public:

    int x;
    int y;
    int health;
    int aiState;
    int direction;

    void moveEnemy();
    void attackEnemy();

    Enemy(){
        x = 4;
        y = 4;
        direction = 0;
    }

};

#endif // ENEMY_H_INCLUDED
