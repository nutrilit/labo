#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL.h>

class Player
{
public:
    // Deklaracje funkcji i zmiennej członkowskich
    Player();
    void MoveCoordinates(int nx, int ny);
    void MoveLeft();
    void MoveRight();

//private:
    // Zmienne członkowskie
    int x, y, width, height;
    SDL_Rect rect;
};

#endif
