// Copyright Xavier Beheydt. All rights reserved.

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH        200
#define WINDOW_HEIGHT       200
#define WINDOW_TITLE        "SDL2 Sprite Animation"
#define RENDER_DRIVER_INDEX -1
#define FPS                 30
#define MSEC                1000
#define FONT_SIZE           16

#define IMG_POSITION_X 75
#define IMG_POSITION_Y 75

#define SHEET_NB_COLS    7
#define SHEET_NB_ROWS    11
#define SHEET_WIDTH_SPR  50
#define SHEET_HEIGHT_SPR 37
#define NB_SPRITES       72

typedef int bool;
const bool true = 1;
const bool false = 0;

typedef struct sSprite_Sheet
{
    int nbCols;
    int nbRows;
    int widthSpr;
    int heightSpr;
} sSprite_Sheet;

typedef struct sSprite_Anim
{
    int         start;
    int         end;
    const char *name;
} sSprite_Anim;

typedef struct sSprite_Pos
{
    SDL_Rect rect;
} sSprinte_Pos;

typedef struct sSDL_ctx
{
    SDL_Window   *window;
    SDL_Renderer *renderer;
    TTF_Font     *font;
    SDL_Texture  *font_tex;
} sSDL_ctx;

static const sSprite_Sheet sheet = {SHEET_NB_COLS, SHEET_NB_ROWS,
                                    SHEET_WIDTH_SPR, SHEET_HEIGHT_SPR};

static const sSprite_Anim idle1 = {0, 3, "idle1\n"};
static const sSprite_Anim crouch = {4, 7, "crouch"};
static const sSprite_Anim run = {8, 13, "run"};
static const sSprite_Anim jump = {14, 17, "jump"};
static const sSprite_Anim mid = {18, 21, "mid"};
static const sSprite_Anim fall = {22, 23, "fall"};
static const sSprite_Anim slide = {24, 28, "slide"};
static const sSprite_Anim grab = {29, 32, "grab"};
static const sSprite_Anim climb = {33, 37, "climb"};
static const sSprite_Anim idle2 = {38, 41, "idle2"};
static const sSprite_Anim attack1 = {42, 46, "attack1"};
static const sSprite_Anim attack2 = {47, 52, "attack2"};
static const sSprite_Anim attack3 = {53, 58, "attack3"};
static const sSprite_Anim hurt = {59, 61, "hurt"};
static const sSprite_Anim die = {62, 68, "die"};
static const sSprite_Anim jump2 = {69, 71, "jump2"};

static void assign_animation(sSDL_ctx          *ctx,
                             sSprite_Anim      *anim,
                             const sSprite_Anim selected)
{
    anim->start = selected.start;
    anim->end = selected.end;
    // FIXME : Rendering after sprite change
    // SDL_Color    col = {255, 0, 0, 255};
    // SDL_Surface *sur =
    //     TTF_RenderUTF8_Blended_Wrapped(ctx->font, "test\n", col, 300);
    // SDL_Texture *tex = SDL_CreateTextureFromSurface(ctx->renderer, sur);
    // SDL_Rect     rect = {0, 0, sur->w, sur->h};
    // SDL_FreeSurface(sur);
    // SDL_RenderCopy(ctx->renderer, tex, NULL, &rect);
    // SDL_RenderPresent(ctx->renderer);
    // SDL_DestroyTexture(tex);
}

static void frame_delay(clock_t start, clock_t now, uint8_t nb_spr)
{
    // FIXME
    double t = (now - start) / (double)CLOCKS_PER_SEC;
    double delay = ((1 / (FPS / (double)nb_spr)) - t) * MSEC;
    if (delay > 0)
        SDL_Delay((Uint32)delay);
}

static bool handling_events(sSDL_ctx     *ctx,
                            sSprite_Anim *current,
                            uint8_t      *frame)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            return (true);
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                return (true);
            else if (e.key.keysym.scancode == SDL_SCANCODE_Q)
                assign_animation(ctx, current, idle1);
            else if (e.key.keysym.scancode == SDL_SCANCODE_W)
                assign_animation(ctx, current, crouch);
            else if (e.key.keysym.scancode == SDL_SCANCODE_E)
                assign_animation(ctx, current, run);
            else if (e.key.keysym.scancode == SDL_SCANCODE_R)
                assign_animation(ctx, current, jump);
            else if (e.key.keysym.scancode == SDL_SCANCODE_T)
                assign_animation(ctx, current, mid);
            else if (e.key.keysym.scancode == SDL_SCANCODE_Y)
                assign_animation(ctx, current, fall);
            else if (e.key.keysym.scancode == SDL_SCANCODE_U)
                assign_animation(ctx, current, slide);
            else if (e.key.keysym.scancode == SDL_SCANCODE_I)
                assign_animation(ctx, current, grab);
            else if (e.key.keysym.scancode == SDL_SCANCODE_O)
                assign_animation(ctx, current, climb);
            else if (e.key.keysym.scancode == SDL_SCANCODE_P)
                assign_animation(ctx, current, idle2);
            else if (e.key.keysym.scancode == SDL_SCANCODE_A)
                assign_animation(ctx, current, attack1);
            else if (e.key.keysym.scancode == SDL_SCANCODE_S)
                assign_animation(ctx, current, attack2);
            else if (e.key.keysym.scancode == SDL_SCANCODE_D)
                assign_animation(ctx, current, attack3);
            else if (e.key.keysym.scancode == SDL_SCANCODE_F)
                assign_animation(ctx, current, hurt);
            else if (e.key.keysym.scancode == SDL_SCANCODE_G)
                assign_animation(ctx, current, die);
            else if (e.key.keysym.scancode == SDL_SCANCODE_H)
                assign_animation(ctx, current, jump2);
            *frame = 0;
        }
    }
    return (false);
}

static void init_sprite_rect(const sSprite_Sheet sheet, SDL_Rect *sprites)
{
    int i = 0;
    for (int y = 0; y < sheet.nbRows; y++)
    {
        for (int x = 0; x < sheet.nbCols; x++)
        {
            sprites[i].x = x * sheet.widthSpr;
            sprites[i].y = y * sheet.heightSpr;
            sprites[i].w = sheet.widthSpr;
            sprites[i].h = sheet.heightSpr;
            ++i;
            if (i == NB_SPRITES)
                return;
        }
    }
}

static void clean_app(sSDL_ctx *ctx)
{
    if (ctx->renderer)
        SDL_DestroyRenderer(ctx->renderer);
    if (ctx->window)
        SDL_DestroyWindow(ctx->window);
    IMG_Quit();
    SDL_Quit();
    TTF_CloseFont(ctx->font);
}

static SDL_Texture *load_tex(sSDL_ctx *ctx, const char *path)
{
    SDL_Surface *surf = IMG_Load(path);
    if (!surf)
    {
        printf("[ERROR] SDL2 failed to load image: %s\n", SDL_GetError());
        clean_app(ctx);
        exit(EXIT_FAILURE);
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ctx->renderer, surf);
    SDL_FreeSurface(surf);
    if (!tex)
    {
        printf("[ERROR] SDL2 failed to create texture from surface: %s\n",
               SDL_GetError());
        clean_app(ctx);
        exit(EXIT_FAILURE);
    }
    return (tex);
}

static void init_app(sSDL_ctx *ctx)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        printf("[ERROR] SDL2 failed to initialize : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        printf("[ERROR] SDL2_image failed to initialize PNG: %s\n",
               SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() < 0)
    {
        printf("[ERROR] SDL2_ttf failed to initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ctx->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                   WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (ctx->window == NULL)
    {
        printf("[ERROR] SDL2 failed to create window: %s\n", SDL_GetError());
        clean_app(ctx);
        exit(EXIT_FAILURE);
    }
    ctx->renderer = SDL_CreateRenderer(ctx->window, RENDER_DRIVER_INDEX,
                                       SDL_RENDERER_ACCELERATED);
    if (ctx->renderer == NULL)
    {
        printf("[ERROR] SDL2 failed to create renderer: %s\n", SDL_GetError());
        clean_app(ctx);
        exit(EXIT_FAILURE);
    }
    ctx->font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (ctx->font == NULL)
    {
        printf("[ERROR] SDL2_ttf failed to open font: %s\n", TTF_GetError());
        clean_app(ctx);
        exit(EXIT_FAILURE);
    }
}

/* Main function =============================================================*/
int main(int argc, char **argv)
{
    SDL_Rect     sprites[NB_SPRITES];
    sSDL_ctx     ctx = {NULL, NULL, NULL, NULL};
    SDL_Rect     pos = {IMG_POSITION_X, IMG_POSITION_Y, SHEET_WIDTH_SPR,
                        SHEET_HEIGHT_SPR};
    sSprite_Anim current = {0, 0};
    bool         done = false;
    clock_t      t1 = 0;
    uint8_t      frame = 0;

    init_app(&ctx);
    init_sprite_rect(sheet, sprites);
    SDL_Texture *tex = load_tex(&ctx, SPRITE_IMAGE);
    assign_animation(&ctx, &current, idle1);

    // Rendering loop
    while (!done)
    {
        t1 = clock();
        SDL_RenderClear(ctx.renderer);
        if (current.start + frame >= current.end + 1)
            frame = 0;
        done = handling_events(&ctx, &current, &frame);
        SDL_RenderCopy(ctx.renderer, tex, &sprites[current.start + frame],
                       &pos);
        SDL_RenderPresent(ctx.renderer);
        // XXX : precalculate frame delay by animation
        frame_delay(t1, clock(), current.end - current.start + 1);
        frame++;
    }
    SDL_DestroyTexture(tex);
    clean_app(&ctx);
    return (EXIT_SUCCESS);
}
