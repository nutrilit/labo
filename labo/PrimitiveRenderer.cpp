#include "PrimitiveRenderer.h"

//zad2 lab2
void PrimitiveRenderer::Draw(SDL_Renderer* renderer, SDL_Rect rect1, SDL_Color color)
{
    //this->rect = { 100, 100, 4, 9 };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect1);
}

//zad3 lab2
void PrimitiveRenderer::RysLinie(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, SDL_Color color)
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
                SDL_Rect rect = { x, y, 3, 3 };
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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
                SDL_Rect rect = { x, y, 3, 3 };
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &rect);
                temp -= dx;
                if (temp < 0)
                {
                    x += tempX;
                    temp += dy;
                }
            }
        }
        SDL_Rect rect = { x1, y1, 3, 3 };
        //SDL_SetRenderDrawColor(renderer, 255, 100, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
    
}
/*
void PrimitiveRenderer::Otwarta(SDL_Renderer* renderer, Point2D nazwa[]) {
    for (int i = 0; i<3; i++) {
        if (i+1<3)
            RysLinie(renderer, nazwa[i].GetX(), nazwa[i].GetY(), nazwa[i + 1].GetX(), nazwa[i + 1].GetY());
    }

}*/

// linia otwarta lub zamknieta wykorzystuje zbiór punktów Point2D
void PrimitiveRenderer::DrawPolyline(SDL_Renderer* renderer, const std::vector<Point2D>& points, bool closed, SDL_Color color)
{
    if (points.size() < 2) {
        return;
    }

    for (size_t i = 1; i < points.size(); ++i) {
        const Point2D& start = points[i - 1];
        const Point2D& end = points[i];
        RysLinie(renderer, start.GetX(), start.GetY(), end.GetX(), end.GetY(), color);
    }

    if (closed && !points.empty()) {
        const Point2D& first = points.front();
        const Point2D& last = points.back();
        RysLinie(renderer, last.GetX(), last.GetY(), first.GetX(), first.GetY(), color);
    }
    
}
 
// Rozszerzona metoda do rysowania linii ³amanej na podstawie odcinków
void PrimitiveRenderer::DrawPolyline2(SDL_Renderer* renderer, const std::vector<LineSegment>& segments, bool closed, SDL_Color color)
{
    if (segments.empty()) {
        return;
    }

    for (size_t i = 0; i < segments.size(); ++i) {
        const LineSegment& segment = segments[i];
        RysLinie(renderer, segment.GetStartPoint().GetX(), segment.GetStartPoint().GetY(), segment.GetEndPoint().GetX(), segment.GetEndPoint().GetY(), color);
    }

    if (closed && segments.size() >= 2) {
        const LineSegment& firstSegment = segments.front();
        const LineSegment& lastSegment = segments.back();
        RysLinie(renderer, lastSegment.GetEndPoint().GetX(), lastSegment.GetEndPoint().GetY(), firstSegment.GetStartPoint().GetX(), firstSegment.GetStartPoint().GetY(), color);
    }
}


// zad1 lab3 rysowanie okregu
void PrimitiveRenderer::DrawCircle4Symmetry(SDL_Renderer* renderer, int x0, int y0, int R, SDL_Color color)
{
    float alpha;
    for (alpha = 0; alpha < M_PI / 2; alpha += 0.005) {
        int x = (x0 + R * cos(alpha));
        int y = (y0 + R * sin(alpha));
        int mirroredX = x0 - (x - x0);
        int mirroredY = y0 - (y - y0);
        Draw(renderer, { x, y, 1, 1 }, color); // Punkt w pierwszej cwiartce
        Draw(renderer, { mirroredX, y, 1, 1 }, color); // Punkt w drugiej æwiartce
        Draw(renderer, { x, mirroredY, 1, 1 }, color); // Punkt w czwartej æwiartce
        Draw(renderer, { mirroredX, mirroredY, 1, 1 }, color); // Punkt w trzeciej æwiartce
    }
}

void PrimitiveRenderer::DrawCircleWithSDL(SDL_Renderer* renderer, int x0, int y0, int R, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int r = R;
    int x = r;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void PrimitiveRenderer::DrawEllipse(SDL_Renderer* renderer, int x0, int y0, int RX, int RY, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    double alpha;
    double step = M_PI / 180; // Krok 1 stopnia

    for (alpha = 0; alpha < M_PI / 2; alpha += step)
    {
        int x = (x0 + RX * cos(alpha));
        int y = (y0 + RY * sin(alpha));
        int mirroredX = x0 - (x - x0);
        int mirroredY = y0 - (y - y0);
        Draw(renderer, { x, y, 1, 1 }, color); // Punkt w pierwszej cwiartce
        Draw(renderer, { mirroredX, y, 1, 1 }, color); // Punkt w drugiej æwiartce
        Draw(renderer, { x, mirroredY, 1, 1 }, color); // Punkt w czwartej æwiartce
        Draw(renderer, { mirroredX, mirroredY, 1, 1 }, color); // Punkt w trzeciej æwiartce
    }
}
