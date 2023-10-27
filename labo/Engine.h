#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "Player.h"
#include "Point2D.h"
#include "PrimitiveRenderer.h"
#include "LineSegment.h"
#include <iostream>

class Engine
{
public:
    Engine(int x, int y);
    void Run();
    ~Engine();

private:
    PrimitiveRenderer pr1;
    SDL_Window* window;
    SDL_Event event;
    int Width, Height;
    Player p1;
    void MovementHandle();
    SDL_Renderer* renderer;
};

#endif
