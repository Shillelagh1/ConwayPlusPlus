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

void RenderSetPixelCol(int x, int y, int r, int g, int b){
    SDL_Rect R;
    R.x = x*g_step;
    R.y = y*g_step;
    R.w = g_step;
    R.h = g_step;
    SDL_SetRenderDrawColor(g_renderer, r, g, b, 255);
    SDL_RenderFillRect(g_renderer, &R);
}

void RenderSetPixel(int x, int y){
    RenderSetPixelCol(x, y, 255, 255, 255);
}

void RenderPresent(){
    SDL_RenderPresent(g_renderer);
}

void RenderBGrid(){
    int i = 0;
    for(int x = 0; x < g_resolution; x++){
        for(int y = 0; y < g_resolution; y++){
            if(i % 2 == 0){
                RenderSetPixelCol(x, y, 70, 70, 70);
            }
            i ++;
        }
        if(g_resolution % 2 == 0){
            i --;
        }
    }
}