/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include<SDL2/SDL.h>
#include <stdio.h>

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_Texture* texture = NULL;
SDL_Surface* surface = NULL;


 int main(int argc, char ** argv)

{

    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Pixel Drawing",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);

    char pixels[2000];

    while (!quit)
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
    {

        SDL_WaitEvent(&event);


        switch (event.type)

        {

        case SDL_QUIT:

            quit = true;

            break;

        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);

        SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;

}
