#pragma once
#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H
#include <SDL.h>
#include <iostream>

class PrimitiveRenderer
{
public:
    void Draw(SDL_Renderer* renderer, SDL_Rect rect1);
    void RysLinie(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);
    SDL_Rect rect;
};

#endif

