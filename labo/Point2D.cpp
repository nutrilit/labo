//zad4 lab2
#include "Point2D.h"
Point2D::Point2D(int x, int y)
{
    this->x = x;
    this->y = y;
    this->rect = { x, y, 15, 15 };
}
Point2D::Point2D()
{
    this->x = 10;
    this->y = 80;
    this->rect = { 10, 80, 15, 15 };
}

void Point2D::print_xy(int& outX, int& outY)
{
    outX = x;
    outY = y;
    std::cout << "Wspolrzedne punktu: x=" << x << ", y=" << y << std::endl;
}

void Point2D::zmien_punkt(int newX, int newY)
{
    x = newX;
    y = newY;
    rect.x = x;
    rect.y = y;
}

/*
void Point2D::rys_piksel(SDL_Renderer* renderer)
{
    pik1.Draw(renderer, rect);
}*/

int Point2D::GetX() const
{
    return x;
}

int Point2D::GetY() const
{
    return y;
}
