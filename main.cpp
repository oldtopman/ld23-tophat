#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include <iostream>
#include "enemy.h"
#include "player.h"

extern int gameState = 1; // 0= init 1= playermove 2=playerattack 3=enemymove 4=enemyattack



int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 640, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* playerUp = SDL_LoadBMP("playerup.bmp");
    SDL_Surface* playerDown = SDL_LoadBMP("playerdown.bmp");
    SDL_Surface* playerLeft = SDL_LoadBMP("playerleft.bmp");
    SDL_Surface* playerRight = SDL_LoadBMP("playerright.bmp");

    SDL_Surface* playerProjectileDown = SDL_LoadBMP("playerprojectiledown.bmp");
    SDL_Surface* playerProjectileUp = SDL_LoadBMP("playerprojectileup.bmp");
    SDL_Surface* playerProjectileLeft = SDL_LoadBMP("playerprojectileleft.bmp");
    SDL_Surface* playerProjectileRight = SDL_LoadBMP("playerprojectileright.bmp");

    SDL_Surface* enemyFlame = SDL_LoadBMP("enemyflame.bmp");

    SDL_Surface* enemyUp = SDL_LoadBMP("enemyup.bmp");
    SDL_Surface* enemyDown = SDL_LoadBMP("enemydown.bmp");
    SDL_Surface* enemyLeft = SDL_LoadBMP("enemyleft.bmp");
    SDL_Surface* enemyRight = SDL_LoadBMP("enemyright.bmp");



    SDL_Surface* bmp = SDL_LoadBMP("background.bmp");
    if (!bmp || !playerUp || !playerDown || !playerLeft || !playerRight || !enemyUp || !enemyDown || !enemyLeft || !enemyRight)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    Player thePlayer;
    Enemy theEnemy;
    time_t oldSeconds;
    time_t seconds;

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // DRAWING STARTS HERE

        SDL_BlitSurface(bmp, 0, screen, &dstrect);


        SDL_Rect playerRect;
        playerRect.x = thePlayer.x*80;
        playerRect.y = thePlayer.y*80;

        SDL_Rect enemyRect;
        enemyRect.x = theEnemy.x*80;
        enemyRect.y = theEnemy.y*80;

        SDL_Rect playerProjectileRect;

        // draw bitmap
        switch(thePlayer.direction){
            case 0:
                SDL_BlitSurface(playerUp, 0, screen, &playerRect);
            break;
            case 1:
                SDL_BlitSurface(playerRight, 0, screen, &playerRect);
            break;
            case 2:
                SDL_BlitSurface(playerDown, 0, screen, &playerRect);
            break;
            case 3:
                SDL_BlitSurface(playerLeft, 0, screen, &playerRect);
            break;
        }


        switch(theEnemy.direction){
            case 0:
                SDL_BlitSurface(enemyUp, 0, screen, &enemyRect);
            break;
            case 1:
                SDL_BlitSurface(enemyRight, 0, screen, &enemyRect);
            break;
            case 2:
                SDL_BlitSurface(enemyDown, 0, screen, &enemyRect);
            break;
            case 3:
                SDL_BlitSurface(enemyLeft, 0, screen, &enemyRect);
            break;
        }



        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
                /* Look for a keypress */
                case SDL_KEYDOWN:
                    /* Check the SDLKey values and move change the coords */
                    switch( event.key.keysym.sym ){
                        case SDLK_LEFT:
                            if (gameState == 1){thePlayer.moveLeft();gameState = 2;}
                        break;
                        case SDLK_RIGHT:
                            if (gameState == 1){thePlayer.moveRight();gameState = 2;}
                        break;
                        case SDLK_UP:
                            if (gameState == 1){thePlayer.moveUp();gameState = 2;}
                        break;
                        case SDLK_DOWN:
                            if (gameState == 1){thePlayer.moveDown();gameState = 2;}
                        break;
                        default:
                            break;
                    }
            }
        }

        if (gameState == 3){theEnemy.moveEnemy();}

        if (gameState == 4){theEnemy.attackEnemy();}

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);
    SDL_FreeSurface(playerUp);
    SDL_FreeSurface(playerDown);
    SDL_FreeSurface(playerLeft);
    SDL_FreeSurface(playerRight);
    SDL_FreeSurface(enemyUp);
    SDL_FreeSurface(enemyDown);
    SDL_FreeSurface(enemyLeft);
    SDL_FreeSurface(enemyRight);
    SDL_FreeSurface(playerProjectileDown);
    SDL_FreeSurface(playerProjectileUp);
    SDL_FreeSurface(playerProjectileLeft);
    SDL_FreeSurface(playerProjectileRight);
    SDL_FreeSurface(enemyFlame);


    // all is well :)
    printf("Exited cleanly\n");
    return 0;
}
