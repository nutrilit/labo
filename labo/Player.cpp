#include "Player.h"

Player::Player()
{
    this->x = 10;
    this->y = 10;
    this->width = 30;
    this->height = 30;
    this->rect = { x, y, width, height };
}

void Player::MoveCoordinates(int nx, int ny)
{
    this->x = nx;
    this->y = ny;
    this->rect = { x, y, width, height };
}

void Player::MoveLeft()
{
    if (x > 0)
        x = x - 10;
    this->rect = { x, y, width, height };
}

void Player::MoveRight()
{
    if (x + width < 800) // w przyszlosci dac rozdzielczosc nie sztywna wartosc
        x = x + 10;
    this->rect = { x, y, width, height };
}
