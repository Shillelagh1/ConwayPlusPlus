#include <stdlib.h>
#include <SDL2/SDL.h>

void RenderSetup(int, int);
void RenderDestroy();
bool RenderIsExit();
void RenderClear();
void RenderSetPixel(int, int);
void RenderPresent();