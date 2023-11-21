#pragma once
#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H
#include <SDL.h>
#include <iostream>
#include "Point2D.h"
#include <vector>
#include "LineSegment.h"
#include <stack>
#include <array>
class PrimitiveRenderer
{
public:
    void Draw(SDL_Renderer* renderer, SDL_Rect rect1, SDL_Color color);
    void RysLinie(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, SDL_Color color);
    SDL_Rect rect;
    //Point2D* dynamicznaKlasa = new Point2D(10, 20);
    void Otwarta(SDL_Renderer* renderer, Point2D nazwa[]);
    void DrawPolyline(SDL_Renderer* renderer, const std::vector<Point2D>& points, bool closed = false, SDL_Color color = { 255, 255, 255, 255 });
    void DrawPolyline2(SDL_Renderer* renderer, const std::vector<LineSegment>& segments, bool closed, SDL_Color color = { 255, 255, 255, 255 });
    void DrawCircle4Symmetry(SDL_Renderer* renderer, int x0, int y0, int R, SDL_Color color = { 255, 255, 255, 255 });
    void DrawEllipse(SDL_Renderer* renderer, int x0, int y0, int RX, int RY, SDL_Color color = { 255, 255, 255, 255 });
    void DrawPolygon(SDL_Renderer* renderer, const std::vector<Point2D>& vertices, SDL_Color color = { 255, 255, 255, 255 });
    void DrawPolygon2(SDL_Renderer* renderer, const std::vector<LineSegment>& segments, SDL_Color color = { 255, 255, 255, 255 });
    void floodFill(SDL_Renderer* renderer, int x, int y, SDL_Color targetColor, SDL_Color fillColor);
};

#endif