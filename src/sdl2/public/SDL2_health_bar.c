// Copyright Xavier Beheydt. All rights reserved.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

#define WINDOW_WIDTH        800
#define WINDOW_HEIGHT       600
#define WINDOW_TITLE        "SDL2 Health Bar"
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

    SDL_Surface *healthbar_sur = IMG_Load(HEALTHBAR_IMAGE);
    if (healthbar_sur == NULL)
    {
        printf("[ERROR] SDL2 failed to load image from IMG_Load: %s\n",
               IMG_GetError());
        return (EXIT_FAILURE);
    }

    SDL_Texture *healthbar_tex =
        SDL_CreateTextureFromSurface(renderer, healthbar_sur);
    if (healthbar_tex == NULL)
    {
        printf("[ERROR] SDL2 failed to create texture from surface: %s\n",
               SDL_GetError());
        return (EXIT_FAILURE);
    }
    SDL_FreeSurface(healthbar_sur);

    SDL_Rect rect = {100, 100, 200, 22};

    int x = 196;

    while (TRUE)
    {
        SDL_Event e;
        if (SDL_WaitEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
            if (e.type == SDL_MOUSEMOTION)
            {
                x = e.motion.x;

                if (x < 196)
                    x = 196;

                if (x > 392)
                    x = 392;
            }
        }
        SDL_Rect rect2 = {102, 102, (x - 196), 18};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, healthbar_tex, NULL, &rect);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect2);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(healthbar_tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return (EXIT_SUCCESS);
}
