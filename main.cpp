#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define fps 60

// You shouldn't really use this statement, but it's fine for small programs
using namespace std;

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {

        // Pointers to our window and surface
        SDL_Surface* winSurface = NULL;
        SDL_Window* window = NULL;

        // Initialize SDL. SDL_Init will return -1 if it fails.
        if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
                cout << "Error initializing SDL: " << SDL_GetError() << endl;
                system("sleep 5");
                // End the program
                return 1;
        }

        // Initialize SDL-PNG LIB
        if (IMG_Init(IMG_INIT_PNG) == 0) {
        cout << "Error SDL2_image Initialization";
        return 2;
    }

        // Create our window
        window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );

        // Make sure creating the window succeeded
        if ( !window ) {
                cout << "Error creating window: " << SDL_GetError()  << endl;
                system("sleep 5");
                // End the program
                return 1;
        }

        // create renderer
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Error renderer creation";
        return 4;
    }

        // Get the surface from the window
        winSurface = SDL_GetWindowSurface( window );

        // Make sure getting the surface succeeded
        if ( !winSurface ) {
                cout << "Error getting surface: " << SDL_GetError() << endl;
                system("sleep 5");
                // End the program
                return 1;
        }

        SDL_Surface* image_sur = IMG_Load("image.png");
    if (image_sur == NULL) {
        std::cout << "Error loading image: " << IMG_GetError();
        return 5;
    }

        SDL_Texture* image_tex = SDL_CreateTextureFromSurface(renderer, image_sur);
    if (image_tex == NULL) {
        std::cout << "Error creating texture";
        return 6;
    }

        SDL_FreeSurface(image_sur);

        Uint32 white = SDL_MapRGB(winSurface->format,255,255,255);
        SDL_FillRect(winSurface,NULL,white);

        SDL_UpdateWindowSurface(window);

        Uint32 starting_tick;
        SDL_Event event;
        bool running = true;
        while (running)
        {
                starting_tick = SDL_GetTicks();
                while (SDL_PollEvent(&event))
                {
                        if( event.type == SDL_QUIT){
                                running = false;
                                break;
                        }
                        if (event.type == SDL_WINDOWEVENT)
                        {
                                if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                                        winSurface = SDL_GetWindowSurface( window );
                                        SDL_FillRect(winSurface,NULL,white);
                                        SDL_UpdateWindowSurface(window);
                                }
                        }
                        if( (1000/ fps) > SDL_GetTicks() - starting_tick){
                                SDL_Delay( 1000/fps - ( SDL_GetTicks() - starting_tick));
                        }
                        SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, image_tex, NULL, NULL);
            SDL_RenderPresent(renderer);

                }

        }
        SDL_DestroyTexture(image_tex);

    SDL_DestroyRenderer(renderer);

        // Destroy the window. This will also destroy the surface
        SDL_DestroyWindow( window );

        IMG_Quit();

        // Quit SDL
        SDL_Quit();

        // End the program
        return 0;
