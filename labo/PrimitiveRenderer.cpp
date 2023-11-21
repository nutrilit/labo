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

// zad2 lab3 rysowanie elipsy
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

// zad3 lab3 

void PrimitiveRenderer::DrawPolygon(SDL_Renderer* renderer, const std::vector<Point2D>& vertices, SDL_Color color)
{
    if (vertices.size() < 3) {
        return;  // Wielok¹t musi mieæ co najmniej 3 wierzcho³ki
    }


    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (size_t i = 0; i < vertices.size() - 1; ++i) {
        const Point2D& start = vertices[i];
        const Point2D& end = vertices[i + 1];
        SDL_RenderDrawLine(renderer, start.GetX(), start.GetY(), end.GetX(), end.GetY());
    }

    // Ostatni odcinek ³¹czy ostatni wierzcho³ek z pierwszym
    const Point2D& first = vertices.front();
    const Point2D& last = vertices.back();
    SDL_RenderDrawLine(renderer, last.GetX(), last.GetY(), first.GetX(), first.GetY());
}

void PrimitiveRenderer::DrawPolygon2(SDL_Renderer* renderer, const std::vector<LineSegment>& segments, SDL_Color color)
{
    // SprawdŸ, czy odcinki przecinaj¹ siê
    for (size_t i = 0; i < segments.size(); ++i) {
        for (size_t j = i + 1; j < segments.size(); ++j) {
            if (segments[i].DoNotIntersect(segments[j])) {
                return;  // Przerwij rysowanie w przypadku przeciêcia
            }
        }
    }

    // Narysuj zamkniêty wielok¹t
    for (const LineSegment& segment : segments) {
        RysLinie(renderer, segment.GetStartPoint().GetX(), segment.GetStartPoint().GetY(),
            segment.GetEndPoint().GetX(), segment.GetEndPoint().GetY(), color);
    }

    // Dodaj ostatni odcinek ³¹cz¹cy pocz¹tek z koñcem
    const LineSegment& firstSegment = segments.front();
    const LineSegment& lastSegment = segments.back();
    RysLinie(renderer, lastSegment.GetEndPoint().GetX(), lastSegment.GetEndPoint().GetY(),
        firstSegment.GetStartPoint().GetX(), firstSegment.GetStartPoint().GetY(), color);
}


void PrimitiveRenderer::floodFill(SDL_Renderer* renderer, int x, int y, SDL_Color targetColor, SDL_Color fillColor) {
    std::stack<std::pair<int, int>> pixelsToCheck;
    pixelsToCheck.push(std::make_pair(x, y));

    std::vector<std::vector<bool>> visited(800, std::vector<bool>(600, false));

    while (!pixelsToCheck.empty()) {
        std::pair<int, int> currentPixel = pixelsToCheck.top();
        pixelsToCheck.pop();

        int px = currentPixel.first;
        int py = currentPixel.second;
        if (visited[px][py]) {
            continue;
        }
        visited[px][py] = true;
        // Pobierz kolor piksela z renderera
        SDL_Color currentColor;
        SDL_Rect pixelRect = { px, py, 1, 1 };
        SDL_RenderReadPixels(renderer, &pixelRect, SDL_PIXELFORMAT_RGBA8888, &currentColor, sizeof(Uint32));
        //std::cout << (int)currentColor.r << (int)currentColor.g << (int)currentColor.b << (int)currentColor.a;
        // SprawdŸ, czy aktualny piksel ma docelowy kolor

        if (currentColor.a == 0 && currentColor.b == 0 &&
            currentColor.g == 0 && currentColor.r == 255) {
            // Ustaw kolor wype³nienia na pikselu
            SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
            //SDL_RenderDrawPoint(renderer, px, py);
            SDL_Rect r1 = { px,py,1,1 };
            SDL_RenderFillRect(renderer, &r1);

            // Dodaj s¹siednie piksele do sprawdzenia
            pixelsToCheck.push(std::make_pair(px + 1, py));
            pixelsToCheck.push(std::make_pair(px - 1, py));
            pixelsToCheck.push(std::make_pair(px, py + 1));
            pixelsToCheck.push(std::make_pair(px, py - 1));

        }
    }
}

//test1