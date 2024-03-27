#include <stdlib.h>
#include "render.h"
#include <SDL2/SDL.h>

SDL_Renderer *g_renderer;
SDL_Window *g_window;
int g_win_size;
int g_resolution;
int g_step;

void RenderSetup(int win_size, int resolution) {

    g_win_size = win_size;
    g_resolution = resolution;
    g_step = win_size/resolution;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(win_size, win_size, 0, &g_window, &g_renderer);
}

void RenderDestroy(){
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}

bool RenderIsExit(){
    SDL_Event event;
    return SDL_PollEvent(&event) && event.type == SDL_QUIT;
}

void RenderClear(){
    SDL_SetRenderDrawColor(g_renderer, 80, 80, 80, 255);
    SDL_RenderClear(g_renderer);
    SDL_RenderPresent(g_renderer);
}

void RenderSetPixel(int x, int y){
    SDL_Rect r;
    r.x = x*g_step;
    r.y = y*g_step;
    r.w = g_step;
    r.h = g_step;
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(g_renderer, &r);
}

void RenderPresent(){
    SDL_RenderPresent(g_renderer);
}