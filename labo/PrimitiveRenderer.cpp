#include "PrimitiveRenderer.h"

//zad2 lab2
void PrimitiveRenderer::Draw(SDL_Renderer* renderer, SDL_Rect rect1)
{
    //this->rect = { 100, 100, 4, 9 };
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderFillRect(renderer, &rect1);
}

//zad3 lab2
void PrimitiveRenderer::RysLinie(SDL_Renderer* renderer, int x0, int y0, int x1, int y1)
{
        int x, y, tempX, tempY;
        float dy, dx, m;
        dy = (y1 - y0) < 0 ? -(y1 - y0) : (y1 - y0);
        dx = (x1 - x0) < 0 ? -(x1 - x0) : (x1 - x0);
        tempX = x0 < x1 ? 1 : -1;
        tempY = y0 < y1 ? 1 : -1;

        if (dx > dy)
        {
            int temp = dx / 2;
            y = y0;
            for (x = x0; x != x1; x += tempX)
            { // zast¹piæ warunek fora
                SDL_Rect rect = { x, y, 10, 10 };
                SDL_SetRenderDrawColor(renderer, 255, 100, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
                temp -= dy;
                if (temp < 0)
                {
                    y += tempY;
                    temp += dx;
                }
            }
        }
        else
        {
            int temp = dy / 2;
            x = x0;
            for (y = y0; y != y1; y += tempY)
            {
                SDL_Rect rect = { x, y, 10, 10 };
                SDL_SetRenderDrawColor(renderer, 255, 100, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
                temp -= dx;
                if (temp < 0)
                {
                    x += tempX;
                    temp += dy;
                }
            }
        }
        SDL_Rect rect = { x1, y1, 10, 10 };
        SDL_SetRenderDrawColor(renderer, 255, 100, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
    
}

void PrimitiveRenderer::Otwarta(SDL_Renderer* renderer, Point2D nazwa[]) {
    for (int i = 0; i < sizeof(nazwa)/(sizeof(nazwa[0])); i++) {
        if (i + 1 <= sizeof(nazwa) / (sizeof(nazwa[0])))
            RysLinie(renderer, nazwa[i].x, nazwa[i].y, nazwa[i + 1].x, nazwa[i + 1].y);
    }

}