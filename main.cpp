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
    int w = 680;
    int h = 480;

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

    SDL_Rect player1 = {20, 20, 20, 80};
    SDL_Rect player2 = {w-40, 20, 20, 80};
    SDL_Rect ball = {40,40,20,20};
    SDL_Point speed = {1,2};

    while (true) {
        SDL_PumpEvents(); // frage nach Input

        const Uint8 * keystate = SDL_GetKeyboardState( nullptr );

        if (keystate[SDL_SCANCODE_Q]){
            break;
        }

        //Fullscreen Toggle
        if (keystate[SDL_SCANCODE_F]){
            if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                // Exit fullscreen
                SDL_SetWindowFullscreen(window, 0);
            } else {
                // Enter fullscreen
                SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
            }
        }

        //player 1 steuerung
        player1.x += keystate[SDL_SCANCODE_D]; // Bewegen des Rechtecks
        player1.x -= keystate[SDL_SCANCODE_A]; // Bewegen nach Links
        player1.y += keystate[SDL_SCANCODE_S]; // nach Unten
        player1.y -= keystate[SDL_SCANCODE_W]; // nach oben

        //player 2 steuerung
        player2.x += keystate[SDL_SCANCODE_L]; // Bewegen des Rechtecks
        player2.x -= keystate[SDL_SCANCODE_J]; // Bewegen nach Links
        player2.y += keystate[SDL_SCANCODE_K]; // nach Unten
        player2.y -= keystate[SDL_SCANCODE_I]; // nach oben

        // move downwards and toches Window down
        if (speed.y > 0 && (ball.y+ball.h) >= h) { // nach unten
            speed.y *= -1;
            //std::cout << "DW + TD" << std::endl;
        }
        //move upwards and touches window up
        if (speed.y < 0 && ball.y <= 0){ // nach oben
            speed.y *= -1;
            //std::cout << "UW + TU" << std::endl;
        }
        // moves left and touches left
        if (speed.x < 0 && ball.x <= 0){
            speed.x *= -1;
            //std::cout << "L + TL" << std::endl;
        }
        // moves right and touches right
        if (speed.x > 0 && (ball.x+ball.w) >= w ){
            speed.x *= -1;
            //std::cout << "R + TR" << std::endl;
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

#if 0
    //zwei objecte berühren sich
    if(SDL_HasIntersection(obj1,obj2))
    if(SDL_HasIntersectionF(obj1,obj2))
#endif
    }

    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    return 0;
}
