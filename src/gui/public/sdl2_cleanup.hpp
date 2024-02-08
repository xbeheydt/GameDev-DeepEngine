// Copyright Xavier Beheydt. All rights reserved.
#pragma once

#include <SDL2/SDL.h>

/**
 * Cleans up SDL2 resources.
 *
 * @param t pointer to SDL2 resource
 * @param args additional SDL2 resources to clean up
 *
 * @return void
 *
 * @throws N/A
 */
template <typename T, typename... Args> void sdl2_cleanup(T *t, Args &&...args)
{
    sdl2_cleanup(t);
    sdl2_cleanup(std::forward<Args>(args)...);
}

/**
 * Clean up an SDL_Window pointer by destroying the window if it exists.
 *
 * @param w SDL_Window pointer to be cleaned up
 *
 * @return void
 *
 * @throws ErrorType None
 */
template <> inline void sdl2_cleanup<SDL_Window>(SDL_Window *w)
{
    if (w)
        SDL_DestroyWindow(w);
}

/**
 * Cleans up an SDL_Renderer object if it is not null.
 *
 * @param r pointer to the SDL_Renderer object to be cleaned up
 *
 * @return void
 *
 * @throws ErrorType if there is an error during cleanup
 */
template <> inline void sdl2_cleanup<SDL_Renderer>(SDL_Renderer *r)
{
    if (r)
        SDL_DestroyRenderer(r);
}

/**
 * Cleans up an SDL_Texture pointer by calling SDL_DestroyTexture if the pointer
 * is not null.
 *
 * @param t Pointer to an SDL_Texture to be cleaned up
 *
 * @return N/A
 *
 * @throws N/A
 */
template <> inline void sdl2_cleanup<SDL_Texture>(SDL_Texture *t)
{
    if (t)
        SDL_DestroyTexture(t);
}

/**
 * Cleans up the SDL_Surface pointer by freeing the memory if it is not null.
 *
 * @param s the SDL_Surface pointer to be cleaned up
 *
 * @return void
 *
 * @throws ErrorType none
 */
template <> inline void sdl2_cleanup<SDL_Surface>(SDL_Surface *s)
{
    if (s)
        SDL_FreeSurface(s);
}

/**
 * Cleans up an SDL_Renderer if it is not null.
 *
 * @param r pointer to the SDL_Renderer to be cleaned up
 *
 * @return void
 *
 * @throws None
 */
template <> inline void sdl2_cleanup<SDL_Renderer>(SDL_Renderer *r)
{
    if (r)
        SDL_DestroyRenderer(r);
}

/**
 * Cleans up an SDL_Texture pointer by calling SDL_DestroyTexture if the pointer
 is not null.
 *
 * @param t Pointer to an SDL_Texture to be cleaned up
 *
 * @return N/A
 *
 * @throws N/A
 */
template <> inline void sdl2_cleanup<SDL_Texture>(SDL_Texture *t)
{
    if (t)
        SDL_DestroyTexture(t);
}

/**
 * Cleans up the SDL_Surface pointer by freeing the memory if it is not null.
 *
 * @param s the SDL_Surface pointer to be cleaned up
 *
 * @return void
 *
 * @throws ErrorType none
 */
template <> inline void sdl2_cleanup<SDL_Surface>(SDL_Surface *s)
{
    if (s)
        SDL_FreeSurface(s);
}
