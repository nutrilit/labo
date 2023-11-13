#include "LineSegment.h"

LineSegment::LineSegment(Point2D start, Point2D end) : start_point(start), end_point(end)
{
    start_point = start;
    end_point = end;
}

Point2D LineSegment::GetStartPoint() const
{
    return start_point;
}

Point2D LineSegment::GetEndPoint() const
{
    return end_point;
}

void LineSegment::SetStartPoint(Point2D new_start)
{
    start_point = new_start;
}

void LineSegment::SetEndPoint(Point2D new_end)
{
    end_point = new_end;
}

void LineSegment::Draw(SDL_Renderer* renderer, bool incremental) const
{
    if (incremental)
    {
        DrawIncremental(renderer);
    }
    else
    {
        DrawDefault(renderer);
    }
}

void LineSegment::DrawDefault(SDL_Renderer* renderer) const
{
    SDL_RenderDrawLine(renderer, start_point.GetX(), start_point.GetY(), end_point.GetX(), end_point.GetY());
}

void LineSegment::DrawIncremental(SDL_Renderer* renderer) const
{
    int x1 = start_point.GetX();
    int y1 = start_point.GetY();
    int x2 = end_point.GetX();
    int y2 = end_point.GetY();

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;

    if (y1 < y2)
        sy = 1;
    else
        sy = -1;

    int err = dx - dy;

    while (x1 != x2 || y1 != y2)
    {
        SDL_RenderDrawPoint(renderer, x1, y1);
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

bool LineSegment::DoNotIntersect(const LineSegment& other) const
{
    const Point2D& p1 = GetStartPoint();
    const Point2D& q1 = GetEndPoint();
    const Point2D& p2 = other.GetStartPoint();
    const Point2D& q2 = other.GetEndPoint();

    if (std::max(p1.GetX(), q1.GetX()) < std::min(p2.GetX(), q2.GetX())) return true;
    if (std::min(p1.GetX(), q1.GetX()) > std::max(p2.GetX(), q2.GetX())) return true;
    if (std::max(p1.GetY(), q1.GetY()) < std::min(p2.GetY(), q2.GetY())) return true;
    if (std::min(p1.GetY(), q1.GetY()) > std::max(p2.GetY(), q2.GetY())) return true;

    std::cerr << "Odcinki siê przecinaj¹!" << std::endl;
    //exit(1);

    return false; 
}

