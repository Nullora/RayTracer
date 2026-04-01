#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
//forget the file parsing i wanna raytrace

int main(){
    const int width=900;
    const int height=600;
    SDL_Window *pwindow = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    Uint8 r,g,b;
    r = 0xff;
    g = 0xff;
    b = 0x00;
    Uint32 color = SDL_MapRGB(psurface->format, r,g,b);
    SDL_FillRect(psurface,NULL,color);
    SDL_UpdateWindowSurface(pwindow);
    int running = 1;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_QUIT){
                running = 0;
            }
        }
        SDL_Delay(20);
    }
}