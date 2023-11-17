#include "PrimitiveRenderer.h"
#include <stack>

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
            { // zastπpiÊ warunek fora
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

// linia otwarta lub zamknieta wykorzystuje zbiÛr punktÛw Point2D
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
 
// Rozszerzona metoda do rysowania linii ≥amanej na podstawie odcinkÛw
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
        Draw(renderer, { mirroredX, y, 1, 1 }, color); // Punkt w drugiej Êwiartce
        Draw(renderer, { x, mirroredY, 1, 1 }, color); // Punkt w czwartej Êwiartce
        Draw(renderer, { mirroredX, mirroredY, 1, 1 }, color); // Punkt w trzeciej Êwiartce
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
        Draw(renderer, { mirroredX, y, 1, 1 }, color); // Punkt w drugiej Êwiartce
        Draw(renderer, { x, mirroredY, 1, 1 }, color); // Punkt w czwartej Êwiartce
        Draw(renderer, { mirroredX, mirroredY, 1, 1 }, color); // Punkt w trzeciej Êwiartce
    }
}

// zad3 lab3 

void PrimitiveRenderer::DrawPolygon(SDL_Renderer* renderer, const std::vector<Point2D>& vertices, SDL_Color color)
{
    if (vertices.size() < 3) {
        return;  // Wielokπt musi mieÊ co najmniej 3 wierzcho≥ki
    }


    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (size_t i = 0; i < vertices.size() - 1; ++i) {
        const Point2D& start = vertices[i];
        const Point2D& end = vertices[i + 1];
        SDL_RenderDrawLine(renderer, start.GetX(), start.GetY(), end.GetX(), end.GetY());
    }

    // Ostatni odcinek ≥πczy ostatni wierzcho≥ek z pierwszym
    const Point2D& first = vertices.front();
    const Point2D& last = vertices.back();
    SDL_RenderDrawLine(renderer, last.GetX(), last.GetY(), first.GetX(), first.GetY());
}

void PrimitiveRenderer::DrawPolygon2(SDL_Renderer* renderer, const std::vector<LineSegment>& segments, SDL_Color color)
{
    // Sprawdü, czy odcinki przecinajπ siÍ
    for (size_t i = 0; i < segments.size(); ++i) {
        for (size_t j = i + 1; j < segments.size(); ++j) {
            if (segments[i].DoNotIntersect(segments[j])) {
                return;  // Przerwij rysowanie w przypadku przeciÍcia
            }
        }
    }

    // Narysuj zamkniÍty wielokπt
    for (const LineSegment& segment : segments) {
        RysLinie(renderer, segment.GetStartPoint().GetX(), segment.GetStartPoint().GetY(),
            segment.GetEndPoint().GetX(), segment.GetEndPoint().GetY(), color);
    }

    // Dodaj ostatni odcinek ≥πczπcy poczπtek z koÒcem
    const LineSegment& firstSegment = segments.front();
    const LineSegment& lastSegment = segments.back();
    RysLinie(renderer, lastSegment.GetEndPoint().GetX(), lastSegment.GetEndPoint().GetY(),
        firstSegment.GetStartPoint().GetX(), firstSegment.GetStartPoint().GetY(), color);
}

void PrimitiveRenderer::BorderFill(SDL_Renderer* renderer, int x, int y, SDL_Color boundaryColor, SDL_Color fillColor)
{
    // Sprawdü czy punkt (x, y) jest poza granicami
    if (x < 0 || x >= 800 || y < 0 || y >= 600)
        return;

    // Sprawdü czy punkt nie jest juø wype≥niony kolorem fillColor
    SDL_Color currentColor;
    SDL_GetRenderDrawColor(renderer, &currentColor.r, &currentColor.g, &currentColor.b, &currentColor.a);
    if (currentColor.r == fillColor.r && currentColor.g == fillColor.g && currentColor.b == fillColor.b) {
        
        SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        SDL_RenderDrawPoint(renderer, x, y);
        return;
    }

    // Sprawdü czy punkt ma kolor boundaryColor
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    if (r != boundaryColor.r || g != boundaryColor.g || b != boundaryColor.b) {
        SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        SDL_RenderDrawPoint(renderer, x, y);
        return;
    }

    // Wype≥nij punkt kolorem fillColor
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderDrawPoint(renderer, x, y);

    // Rekurencyjnie wype≥niaj sπsiednie punkty
    BorderFill(renderer, x + 1, y, boundaryColor, fillColor);
    BorderFill(renderer, x - 1, y, boundaryColor, fillColor);
    BorderFill(renderer, x, y + 1, boundaryColor, fillColor);
    BorderFill(renderer, x, y - 1, boundaryColor, fillColor);
}

void PrimitiveRenderer::FloodFill(SDL_Renderer* renderer, int x, int y, SDL_Color targetColor, SDL_Color fillColor)
{
    // Sprawdü czy punkt (x, y) jest poza granicami
    if (x < 0 || x >= 800 || y < 0 || y >= 600)
        return;

    // Sprawdü czy punkt nie jest juø wype≥niony kolorem fillColor
    SDL_Color currentColor;
    SDL_GetRenderDrawColor(renderer, &currentColor.r, &currentColor.g, &currentColor.b, &currentColor.a);
    if (currentColor.r == fillColor.r && currentColor.g == fillColor.g && currentColor.b == fillColor.b)
        return;

    // Sprawdü czy punkt ma kolor docelowy targetColor
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    if (r != targetColor.r || g != targetColor.g || b != targetColor.b)
        return;

    // Wype≥nij punkt kolorem fillColor
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderDrawPoint(renderer, x, y);

    // Rekurencyjnie wype≥niaj sπsiednie punkty
    FloodFill(renderer, x + 1, y, targetColor, fillColor);
    FloodFill(renderer, x - 1, y, targetColor, fillColor);
    FloodFill(renderer, x, y + 1, targetColor, fillColor);
    FloodFill(renderer, x, y - 1, targetColor, fillColor);
}
SDL_Color getPixelColor(SDL_Renderer* renderer, int pixel_X, int pixel_Y,SDL_Color &c) {
    SDL_Color pixelColor;
    SDL_Surface* getPixel_Surface = SDL_CreateRGBSurface(0, 800, 600, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, getPixel_Surface->pixels, getPixel_Surface->pitch);
    
    const Uint8 getPixel_bpp = getPixel_Surface->format->BytesPerPixel;

    Uint16* pPixel = (Uint16*)getPixel_Surface->pixels + pixel_Y * getPixel_Surface->pitch + pixel_X * getPixel_bpp;

    Uint32 pixelData;

    switch (getPixel_bpp) {
    case 1:
        pixelData = *pPixel;
        break;
    case 2:
        pixelData = *(Uint16*)pPixel;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            pixelData = pPixel[0] << 16 | pPixel[1] << 8 | pPixel[2];
        else
            pixelData = pPixel[0] | pPixel[1] << 8 | pPixel[2] << 16;
        break;
    case 4:
        pixelData = *(Uint32*)pPixel;
        break;
    }

    SDL_GetRGBA(pixelData, getPixel_Surface->format, &pixelColor.r, &pixelColor.g, &pixelColor.b, &pixelColor.a);
    SDL_Color tmp = { pixelColor.r ,pixelColor.g,pixelColor.b,pixelColor.a};
    c = tmp;
    return pixelColor;
}
void PrimitiveRenderer::wypelnij(SDL_Renderer* renderer,int x,int y)
{
    SDL_Color blank = { 0,0,0,0 };
    SDL_Color czarny = { 0,0,0,255 };
    SDL_Color fill = { 255,0,255,0 };
    SDL_Rect rect = { x,y,1,1 };
    Uint8 r, g, b, a;
    int i = 0;
   // SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_Color czerwony = { 255,0,0,255 };
    SDL_Color test = { 0,0,255,255 };
    //Draw(renderer, rect, czerwony);
    SDL_SetRenderDrawColor(renderer, 201, 35, 250 ,25);
    SDL_Rect rect1 = { x,y,1,1 };
    getPixelColor(renderer, x, y, blank);
    //SDL_RenderFillRect(renderer, &rect1);
    int tmpx = x, tmpy = y;

    while (blank.r == 0 && blank.g == 0 && blank.b == 0 && blank.a == 255)//(i < 5);//(r != 0 || g != 0 || b != 0 || a != 255);*/
    {
            Draw(renderer, rect, czerwony);
            //SDL_RenderDrawPoint(renderer, tmpx, tmpy);
            rect.x++;
            tmpx++;
            getPixelColor(renderer, tmpx, tmpy, blank);
            std::cout << (int)blank.r << std::endl << (int)blank.g << std::endl << (int)blank.r << std::endl << (int)blank.a << std::endl;
            // SDL_RenderReadPixels(renderer,&rect1,);
            i++;
            if (blank.r != 0 || blank.g != 0 || blank.b != 0 || blank.a != 255)
            {
                rect.x = x;
                tmpy++;
                getPixelColor(renderer, tmpx, tmpy, blank);
                break;
            }
            // SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
             //getPixelColor(renderer, x, y, blank);
        
    }
}

bool PrimitiveRenderer::isColorEqual(SDL_Color c1,  SDL_Color c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
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
        // Sprawdü, czy aktualny piksel ma docelowy kolor
        
        if (currentColor.a == targetColor.r && currentColor.b == targetColor.g &&
            currentColor.g == targetColor.b && currentColor.r == targetColor.a) {
            // Ustaw kolor wype≥nienia na pikselu
            SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
            //SDL_RenderDrawPoint(renderer, px, py);
            SDL_Rect r1 = { px,py,1,1 };
            SDL_RenderFillRect(renderer,&r1);

            // Dodaj sπsiednie piksele do sprawdzenia
            pixelsToCheck.push(std::make_pair(px + 1, py));
            pixelsToCheck.push(std::make_pair(px - 1, py));
            pixelsToCheck.push(std::make_pair(px, py + 1));
            pixelsToCheck.push(std::make_pair(px, py - 1));
        }
    }
}