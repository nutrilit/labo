#pragma once
#ifndef POINT2D_H
#define POINT2D_H

#include <SDL.h>
//include #"PrimitiveRenderer.h"
#include <iostream>

class Point2D
{
public:
    Point2D(int x, int y);
    int GetX() const;
    int GetY() const;
    void print_xy(int& outX, int& outY);
    void zmien_punkt(int newX, int newY);
    //void rys_piksel(SDL_Renderer* renderer);
    Point2D();
    int x, y;
    //PrimitiveRenderer pik1;
    SDL_Rect rect;
    //SDL_Renderer* renderer;
};

#endif

