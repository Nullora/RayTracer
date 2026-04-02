#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
//background
#define back 0x00000000

typedef struct{
    double x;
    double y;
    Uint32 color;
    double rad;
}Circle;

//x=center x-radius(left boundary) and x+radius(right boundary)
//y=center y-radius(bottom boundary) y+radius(top boundary)
//we loop through each pixel in the boundaries we made. the boundaries are a square surrounding the circle we wanna make.
//if the distance from the center to the current pixel is less than radius, we draw it.
void FillCircle(SDL_Surface* surf, Circle circ){
    //we dont use pow because we want this to run as efficiently as possible
    //pow is made for complex shit not a simple square
    double radius_sqrd = (circ.rad*circ.rad);
    SDL_Rect pix;
    //loop through horizontal pixels
    for(double x=circ.x-circ.rad; x<=circ.x+circ.rad;x++){
        //loop through vertical pixels
        for(double y=circ.y-circ.rad; y<=circ.y+circ.rad;y++){
            //simple pythagorean theorem but we dont find the root of the square to save computation power
            double distance_sqrd = (x - circ.x) * (x - circ.x) + (y - circ.y) * (y - circ.y);
            if(distance_sqrd<radius_sqrd){
                pix = (SDL_Rect){x,y,1,1};
                SDL_FillRect(surf, &pix, circ.color);
            }
        }
    }
}

int main(){
    const int width = 900;
    const int height = 600;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *pwindow = SDL_CreateWindow("Raytracing 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    Uint8 r=0xff,g=0,b=0xff;
    //i do this so i can easily adjust rgb values later without messing with a long ass hex number
    Uint32 color = SDL_MapRGB(psurface->format, r,g,b);
    //background
    SDL_FillRect(psurface, NULL, back);

    Circle circ;
    circ.x = 200; circ.y = 200; circ.rad = 50; circ.color = color;
    FillCircle(psurface, circ);
    SDL_UpdateWindowSurface(pwindow);


    int running = 1;
    SDL_Event e;
    while(running){
        while(SDL_PollEvent(&e)){
            //quit
            if(e.type==SDL_QUIT){
                running = 0;
            }
            if(e.type==SDL_MOUSEMOTION && e.motion.state == SDL_PRESSED){
                circ.x = e.motion.x;
                circ.y = e.motion.y;

            }
        }
        SDL_FillRect(psurface, NULL, back);
        FillCircle(psurface, circ);
        SDL_UpdateWindowSurface(pwindow);
        SDL_Delay(5);
    }
    SDL_Quit();
    return 0;
}