#include <stdlib.h>
#include <iostream>
#include "render.h"
#include <fstream>
#include <SDL2/SDL.h>

int resolution;
int step;
int win_size = 600;

struct pair{
    int x;
    int y;
};

int idxto(int x, int y){
    return (y*resolution) + x;
}

pair idxfrom(int i){
    pair P;
    P.x = i % resolution;
    P.y = i / resolution;
    return P;
}

void RenderState(bool* state){
    RenderClear();
    for(int x = 0; x < resolution; x++){
        for(int y = 0; y < resolution; y++){
            if(state[idxto(x,y)]){
                RenderSetPixel(x, y);
            }
        }
    }
}

bool* LoadSetupState(char* file){
    std::ifstream infile(file);

    resolution = infile.get();

    bool* state;
    state = static_cast<bool*>(malloc(resolution*resolution));
    memset(state, 0, resolution*resolution);
    char x, y;
    while(infile >> x >> y){
        state[idxto(x,y)] = true;
    }
    return state;
}

int EnumerateAdjacents(bool* state, int x, int y){
    int c = 0;

    // genuine brainrot
    for (int xx = x-1; xx <= x+1; xx++){
        for (int yy = y-1; yy <= y+1; yy++){
            if (xx >= 0 && xx < resolution && yy >= 0 && yy < resolution){
                if(xx == x && yy == y)continue;
                if(state[idxto(xx, yy)]){
                    c ++;
                }
            }
        }
    }

    return c;
}

bool* Step(bool* c_state){
    bool* n_state;
    n_state = static_cast<bool*>(malloc(resolution*resolution));
    memset(n_state, 0, resolution*resolution);

    int I;

    int population;
    for(int x = 0; x < resolution; x++){
        for(int y = 0; y < resolution; y++){
            // Each 'cell'
            I = idxto(x, y);

            population = EnumerateAdjacents(c_state, x, y);

            // Persistance State
            if((population == 2 || population == 3) && c_state[I]){
                n_state[I] = true;
            }
            // Reproduction State
            if(population == 3){
                n_state[I] = true;
            }
        }
    }

    // Destroy the previous state
    free(c_state);

    return n_state;
}

void SerializeState(bool* state, const char* fname){
    std::ofstream out(fname);
    out << (char)resolution;

    pair P;
    for(int i = 0; i < resolution*resolution; i++){
        if(state[i]){
            P = idxfrom(i);
            out << (char)P.x;
            out << (char)P.y;
        }
    }

    out.close();
}

int main(int argc, char **argv)
{
    bool* g_state = LoadSetupState(argv[1]);

    if(resolution = -1){
        std::string res;
        std::cout << "Playspace Resolution? ( 0<->255 )";
        std::getline( std::cin, res);
        resolution = atoi(res.c_str());
        if(resolution <= 0){
            resolution = 1;
        }
        if(resolution > 255){
            resolution = 255;
        }
        
        g_state = static_cast<bool*>(malloc(resolution*resolution));
        memset(g_state, 0, resolution*resolution);
    }

    RenderSetup(win_size, resolution);
    step = win_size/resolution;

    RenderState(g_state);
    RenderPresent();

    int ms = 0;
    int ms_t = 0;
    int this_ticks = 0;
    bool isStep = false;
    int step_ms = 400;
    SDL_Event e;

    while(1){
        if(ms > step_ms && isStep){
            g_state = Step(g_state);
            RenderState(g_state);
            ms = 0;
            RenderPresent();
        }

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) goto quit;
            if(e.type == SDL_KEYDOWN && !e.key.repeat){
                switch(e.key.keysym.sym){
                    case SDLK_SPACE:
                        isStep = !isStep;
                        break;
                    case SDLK_DOWN:
                        step_ms += 100;
                        break;
                    case SDLK_UP:
                        step_ms -= 100;
                        if(step_ms<=20){
                            step_ms = 20;
                        }
                        break;
                    case SDLK_TAB:                  // THIS MUST (should) BE LAST ENTRY
                        std::cout<<"FILE NAME:";
                        std::string fn;
                        std::getline( std::cin, fn);
                        SerializeState(g_state, fn.c_str());
                    break;
                }
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){
                int x, y;
                SDL_GetMouseState(&x, &y);
                int N = idxto(x/step, y/step);
                g_state[N] = !g_state[N];
                RenderState(g_state);
                RenderPresent();
            }
        }

        this_ticks = SDL_GetTicks();
        ms += (this_ticks - ms_t);
        ms_t = this_ticks;
    }
    quit:

    RenderDestroy();

    /* code */
    return 0;
}