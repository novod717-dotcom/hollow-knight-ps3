/*
 * Hallownest PS3 Homebrew — prototype gameplay loop.
 * Original placeholder art is drawn with SDL2 primitives.
 * This is a desktop logic prototype, NOT a PS3 executable.
 */
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define W 960
#define H 540
#define FLOOR_Y 440

typedef struct {
    float x, y, vx, vy;
    int facing;
    bool grounded, attacking, dashing;
    int attack_ms, dash_ms;
} Player;

static void rect(SDL_Renderer *r, int x, int y, int w, int h,
                 Uint8 cr, Uint8 cg, Uint8 cb) {
    SDL_Rect q = {x,y,w,h};
    SDL_SetRenderDrawColor(r, cr,cg,cb,255);
    SDL_RenderFillRect(r, &q);
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("HALLownest - prototipo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
    if (!win) { SDL_Quit(); return 1; }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) { SDL_DestroyWindow(win); SDL_Quit(); return 1; }

    Player p = {120, FLOOR_Y-64, 0, 0, 1, true, false, false, 0, 0};
    bool running = true;
    Uint32 last = SDL_GetTicks();

    while (running) {
        Uint32 now = SDL_GetTicks();
        float dt = (now-last)/1000.0f;
        last = now;
        if (dt > 0.05f) dt = 0.05f;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN && !e.key.repeat) {
                if (e.key.keysym.sym == SDLK_ESCAPE) running = false;
                if ((e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP)
                    && p.grounded) { p.vy = -560.0f; p.grounded = false; }
                if (e.key.keysym.sym == SDLK_j && p.attack_ms <= 0) {
                    p.attacking = true; p.attack_ms = 220;
                }
                if (e.key.keysym.sym == SDLK_k && p.dash_ms <= 0) {
                    p.dashing = true; p.dash_ms = 170;
                }
            }
        }

        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        float dir = 0;
        if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) dir -= 1;
        if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) dir += 1;
        if (dir != 0) p.facing = dir > 0 ? 1 : -1;

        if (p.dashing) {
            p.vx = p.facing * 760.0f;
            p.vy = 0;
            p.dash_ms -= (int)(dt*1000);
            if (p.dash_ms <= 0) p.dashing = false;
        } else {
            p.vx = dir * 270.0f;
            p.vy += 1450.0f * dt;
        }
        p.x += p.vx * dt;
        p.y += p.vy * dt;
        if (p.y + 64 >= FLOOR_Y) {
            p.y = FLOOR_Y - 64; p.vy = 0; p.grounded = true;
        } else p.grounded = false;

        if (p.x < 20) p.x = 20;
        if (p.x > W-60) p.x = W-60;
        if (p.attack_ms > 0) {
            p.attack_ms -= (int)(dt*1000);
            if (p.attack_ms <= 0) p.attacking = false;
        }

        SDL_SetRenderDrawColor(ren, 10, 12, 24, 255);
        SDL_RenderClear(ren);
        /* Background layers */
        rect(ren, 0, 350, W, 90, 20, 25, 45);
        rect(ren, 0, FLOOR_Y, W, H-FLOOR_Y, 35, 34, 50);
        for (int i=0; i<12; ++i) rect(ren, i*90+20, 385, 3, 55, 55, 60, 80);
        /* Player placeholder: cloak + mask */
        rect(ren, (int)p.x+12, (int)p.y+26, 34, 38, 25, 27, 45);
        rect(ren, (int)p.x+8, (int)p.y+2, 42, 36, 225, 225, 230);
        rect(ren, (int)p.x+16, (int)p.y+14, 8, 13, 5, 5, 12);
        rect(ren, (int)p.x+34, (int)p.y+14, 8, 13, 5, 5, 12);
        /* Horns */
        rect(ren, (int)p.x+8, (int)p.y-8, 8, 14, 230,230,235);
        rect(ren, (int)p.x+42, (int)p.y-8, 8, 14, 230,230,235);
        /* Nail / attack slash */
        if (p.attacking) {
            int sx = p.facing > 0 ? (int)p.x+48 : (int)p.x-38;
            rect(ren, sx, (int)p.y+28, 42, 5, 210, 220, 240);
            rect(ren, sx+8, (int)p.y+20, 24, 3, 130, 170, 210);
        } else {
            int sx = p.facing > 0 ? (int)p.x+45 : (int)p.x-10;
            rect(ren, sx, (int)p.y+38, 22, 4, 185, 195, 210);
        }
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
