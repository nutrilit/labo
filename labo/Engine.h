#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "Player.h"
#include "Point2D.h"
#include "PrimitiveRenderer.h"
#include "LineSegment.h"
#include <iostream>
#include <vector>

class Engine
{
public:
    Engine(int x, int y);
    void Run();
    ~Engine();

private:
    PrimitiveRenderer pr1,pr2;
    SDL_Color czerwony = { 255,0,0,255 };
    SDL_Color niebieski = { 0,0,255,255 };
    SDL_Color cyraneczka = { 0,128,128,255 };
    SDL_Color zolty = { 255,255,0,255 };
    SDL_Color marynarkawojenna = { 0,0,128, 255 };
    SDL_Window* window;
    SDL_Event event;
    int Width, Height;
    Player p1;
    void MovementHandle();
    SDL_Renderer* renderer;
    std::vector<Point2D> polylinePoints;
    std::vector<LineSegment> polylineSegments;
};

#endif
