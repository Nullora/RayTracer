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
int width;
int height;
//x=center x-radius(left boundary) and x+radius(right boundary)
//y=center y-radius(bottom boundary) y+radius(top boundary)
//we loop through each pixel in the boundaries we made. the boundaries are a square surrounding the circle we wanna make.
//if the distance from the center to the current pixel is less than radius, we draw it.
void FillCircle(SDL_Surface* surf, Circle circ){
    //we dont use pow because we want this to run as efficiently as possible
    //pow is made for complex shit not a simple square
    double radius_sqrd = (circ.rad*circ.rad);

    //we write directly to memory instead of calling fillRect()
    //much much faster this way
    Uint32* pixels = (Uint32*)surf->pixels;
    int pitch = surf->pitch / 4; //pitch is in bytes, convert to pixels


    //  boundaries to prevent segfault
    int startX = circ.x - circ.rad;
    int endX   = circ.x + circ.rad;
    int startY = circ.y - circ.rad;
    int endY   = circ.y + circ.rad;
    //  we assign startX, endX, startY, endY
    //were clipping them to not exceed the boundary and try to access foreign memory
    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX >= surf->w) endX = surf->w - 1;
    if (endY >= surf->h) endY = surf->h - 1;

    //loop through horizontal pixels
    for(int x=startX; x<=endX;x++){
        //loop through vertical pixels
        for(int y=startY; y<=endY;y++){
            //simple pythagorean theorem but we dont find the root of the square to save computation power
            double dx = x - circ.x;
            double dy = y - circ.y;
            if ((dx * dx + dy * dy) <= radius_sqrd){
                //the little equation inside has an explanation in "Documentation/why.md"
                pixels[y * pitch + x] = circ.color;
            }
        }
    }
}
//i made my own FillRect but removed the overhead to make it faster
void FillRect(SDL_Surface* surf, Uint32 color){
    Uint32* pixels = (Uint32*)surf->pixels;
    int pitch = surf->pitch / 4; //same reason, we divide by 4 to convert to pixels
    for(int y = 0; y<surf->h;y++){
        for(int x = 0; x<surf->w;x++){
            pixels[y*pitch+x] = color;
        }
    }
}


int main(){
    width = 1550;
    height = 1000;
    SDL_Window *pwindow = SDL_CreateWindow("heni mfaggas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    Uint8 r=0x00,g=0,b=0xff;
    //i do this so i can easily adjust rgb values later without messing with a long ass hex number
    Uint32 color = SDL_MapRGB(psurface->format, r,g,b);
    //background
    FillRect(psurface, back);

    Circle circ;
    circ.x = 500; circ.y = 500; circ.rad = 50; circ.color = color;
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


            //change circle position
            if(e.type==SDL_MOUSEMOTION && e.motion.state == SDL_PRESSED){
                circ.y = e.motion.y;
                circ.x = e.motion.x;
            }
        }
        FillRect(psurface, back);
        FillCircle(psurface, circ);
        SDL_UpdateWindowSurface(pwindow);
        SDL_Delay(1);
    }
    SDL_Quit();
    return 0;
}