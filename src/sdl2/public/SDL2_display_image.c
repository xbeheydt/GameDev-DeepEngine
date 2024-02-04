// Copyright Xavier Beheydt. All rights reserved.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#define TRUE                1
#define FALSE               0

#define WINDOW_WIDTH        800
#define WINDOW_HEIGHT       600
#define WINDOW_TITLE        "SDL2 Display Image"
#define RENDER_DRIVER_INDEX -1

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        printf("[ERROR] SDL2 failed to initialize : %s\n", SDL_GetError());
        return (EXIT_FAILURE);
    }

    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        printf("[ERROR] SDL2_image failed to initialize PNG: %s\n",
               SDL_GetError());
        return (EXIT_FAILURE);
    }

    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        printf("[ERROR] SDL2 failed to create window: %s\n", SDL_GetError());
        return (EXIT_FAILURE);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, RENDER_DRIVER_INDEX,
                                                SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("[ERROR] SDL2 failed to create renderer: %s\n", SDL_GetError());
        return (EXIT_FAILURE);
    }

    SDL_Surface *lettuce_sur = IMG_Load(LETTUCE_IMAGE);
    if (lettuce_sur == NULL)
    {
        printf("[ERROR] SDL2 failed to load image from IMG_Load: %s\n",
               IMG_GetError());
        return (EXIT_FAILURE);
    }

    SDL_Texture *lettuce_tex =
        SDL_CreateTextureFromSurface(renderer, lettuce_sur);
    if (lettuce_tex == NULL)
    {
        printf("[ERROR] SDL2 failed to create texture from surface: %s\n",
               SDL_GetError());
        return (EXIT_FAILURE);
    }
    SDL_FreeSurface(lettuce_sur);

    while (TRUE)
    {
        SDL_Event e;
        if (SDL_WaitEvent(&e))
            if (e.type == SDL_QUIT)
                break;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, lettuce_tex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(lettuce_tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return (EXIT_SUCCESS);
}
