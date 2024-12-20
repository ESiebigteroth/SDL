#include <iostream>

#ifdef __linux__ 
#   include "SDL2/SDL.h"
#   include "SDL2/SDL_render.h"
#elif _WIN32
    // windows code goes here
#elif __APPLE__
#   include "SDL.h"
#   include "SDL_render.h"
#endif


// player cant escape from window
void inWindow(SDL_Rect *player, int *w, int *h){
    player->x = std::max(0, player->x);
    player->x = std::min(*w - player->w, player->x);
    player->y = std::max(0, player->y);
    player->y = std::min(*h - player->h, player->y);
}

int main()
{
    int wold=0;
    int hold=0;
    int w = 680;
    int h = 480;
    int Score1 = 0;
    int Score2 = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          w, h,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(!window){
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Renderer * renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Rect player1 = {20, h/2-h/12, 20, h/6};
    SDL_Rect player2 = {w-40, h/2-h/12, 20, player1.h};
    SDL_Rect player1hb = {player1.x+player1.w,player1.y,1,player1.h};
    SDL_Rect player2hb = {player2.x,player2.y,1,player2.h};
    SDL_Rect ball = {w/2,h/2,h/30,h/30};
    SDL_Point speed = {1,2};

    while (true) {
        SDL_PumpEvents(); // frage nach Input

        const Uint8 * keystate = SDL_GetKeyboardState( nullptr );

        if (keystate[SDL_SCANCODE_Q]){
            break;
        }

        //Fullscreen Toggle
        if (keystate[SDL_SCANCODE_F]){
            wold = w;
            hold = h;
            if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                // Exit fullscreen
                SDL_SetWindowFullscreen(window, 0);
                //TODO speed des balls erhöhen
            } else {
                // Enter fullscreen
                SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
                //TODO speed des balls veringern
            }
            SDL_GetWindowSize(window,&w,&h);
            //std::cout << "width: " << w << " height: " << h << std::endl;
            player1.h = h/6;
            player1hb.h = player1.h;
            player2.h = h/6;
            player2hb.h = player2.h;
            ball.h = h/30;
            ball.w = h/30;
            player2.x = w-player2.w-20;
            player2hb.x = player2.x;
            std::cout << "W old: " << wold << " W new: " << w << std::endl;
            std::cout << "H old: " << hold << " H new: " << h << std::endl;
            player1.y = ((double )player1.y / hold) * h;
            player2.y = ((double )player2.y / hold) * h;
            ball.x = ((double )ball.x / wold) * w;
            ball.y = ((double )ball.y / hold) * h;

        }

        //player 1 steuerung
        player1.y += keystate[SDL_SCANCODE_S]; // nach Unten
        player1.y -= keystate[SDL_SCANCODE_W]; // nach oben
        player1hb.y = player1.y;

        //player 2 steuerung
        player2.y += keystate[SDL_SCANCODE_K]; // nach Unten
        player2.y -= keystate[SDL_SCANCODE_I]; // nach oben
        player2hb.y = player2.y;

        // move downwards and toches Window down
        if (speed.y > 0 && (ball.y+ball.h) >= h) { // nach unten
            speed.y *= -1;
            ball.y = h-ball.h;
            //std::cout << "DW + TD" << std::endl;
        }
        //move upwards and touches window up
        if (speed.y < 0 && ball.y <= 0){ // nach oben
            speed.y *= -1;
            ball.y = 0;
            //std::cout << "UW + TU" << std::endl;
        }
        // moves left and touches left
        if (speed.x < 0 && ball.x <= 0){
            //speed.x *= -1;
            //ball.x = 0;
            //std::cout << "L + TL" << std::endl;
            std::cout << "Player 2 goal" << std::endl;
            Score2++;
            ball.x = w/2;
            ball.y = h/2;
            speed.x *= -1;
        }
        // moves right and touches right
        if (speed.x > 0 && (ball.x+ball.w) >= w ){
            //speed.x *= -1;
            //ball.x = w-ball.w;
            //std::cout << "R + TR" << std::endl;
            std::cout << "Player 1 goal" << std::endl;
            Score1++;
            ball.x = w/2;
            ball.y = h/2;
            speed.x *= -1;
        }

        if(SDL_HasIntersection(&player1hb,&ball)){
            if ((ball.y > player1hb.y) and ((ball.y+ball.h) < player1hb.y+player1hb.h )) {
                std::cout << "L HIT" << std::endl;
                speed.x *= -1;
            }
        }
        if( SDL_HasIntersection(&player2hb,&ball)){
            if ((ball.y > player2hb.y) and ((ball.y+ball.h) < player2hb.y+player2hb.h )) {
                std::cout << "R HIT" << std::endl;
                speed.x *= -1;
            }
        }

        ball.x += speed.x;
        ball.y += speed.y;

        // Berechne w und h des Windows
        SDL_GetWindowSize(window,&w,&h);

        // Rechteck kann nicht außerhalb des Fensters
        inWindow(&player1,&w,&h);
        inWindow(&player2,&w,&h);

        SDL_SetRenderDrawColor( renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor( renderer, 255, 0,0,255);
        SDL_RenderFillRect( renderer, &player1);
        SDL_RenderFillRect( renderer , &player2);
        SDL_RenderFillRect( renderer, &ball);
        SDL_RenderPresent(renderer); // show rendered frame

    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    std::cout << "Score Player 1: " << Score1 << std::endl;
    std::cout << "Score Player 2: " << Score2 << std::endl;

    return 0;
}
