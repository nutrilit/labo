#pragma once
#include "Point2D.h"
//#include "PrimitiveRenderer.h"
#include <SDL.h>

class LineSegment
{
public:
    LineSegment(Point2D start, Point2D end);
    Point2D GetStartPoint() const;
    Point2D GetEndPoint() const;
    void SetStartPoint(Point2D new_start);
    void SetEndPoint(Point2D new_end);
    void Draw(SDL_Renderer* renderer, bool incremental = false) const;
    bool DoNotIntersect(const LineSegment& other) const;

private:
    Point2D start_point;
    Point2D end_point;
    void DrawDefault(SDL_Renderer* renderer) const;
    void DrawIncremental(SDL_Renderer* renderer) const;
};
