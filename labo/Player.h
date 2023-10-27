#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SDL.h>

class Player
{
public:
    // Deklaracje funkcji i zmiennej cz�onkowskich
    Player();
    void MoveCoordinates(int nx, int ny);
    void MoveLeft();
    void MoveRight();

//private:
    // Zmienne cz�onkowskie
    int x, y, width, height;
    SDL_Rect rect;
};

#endif
