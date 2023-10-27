#include <SDL.h>
#include <iostream>
#include "Player.h" // Dodaj plik nagłówkowy Player
#include "PrimitiveRenderer.h" // Dodaj plik nagłówkowy PrimitiveRenderer
#include "Point2D.h" // Dodaj plik nagłówkowy Point2D
#include "Engine.h" // Dodaj plik nagłówkowy Engine
int main(int argc, char* argv[])
{
    Engine game(800, 600);
    game.Run();
    return 0;
}
