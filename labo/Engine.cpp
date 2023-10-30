#include "Engine.h"

Engine::Engine(int x, int y)
{
    this->Width = x;
    this->Height = y;
    p1.MoveCoordinates(this->Width / 2, this->Height - (p1.height + 5));

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        exit(1);
    }

    window = SDL_CreateWindow("Space Intruders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);

    if (!window)
    {
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        exit(1);
    }
}

void Engine::Run()
{
    // obiekt  Point2D
    Point2D point(5, 5);

    //obiekty Point2D ale do LineSegment
    Point2D point1(5, 5);
    Point2D point2(10, 10);

    // Tworzenie obiektu LineSegment
    LineSegment line(point1, point2);

    //fpsy
    const int FPS = 30;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    float old_time = SDL_GetTicks();
    bool isRunning = true;
    Point2D nazwa[3] = { Point2D(10,15),Point2D(20,20) ,Point2D(200,30) };
    while (isRunning)
    {
        // klatki
        frameStart = SDL_GetTicks();
        /*gracz*/
        //poruszanie sie gracza
        MovementHandle();
        // rysowanie gracza
        pr1.Draw(renderer, p1.rect);
        /* koniec gracz*/
        // rysowanie piksela w lewym gornym rogu
        //point.rys_piksel(renderer);
        // piksel narysowany wyzej zostaje przeniesiony na prawy gorny rog
        point.zmien_punkt(750, 20);

        //test czy dzia³aj¹ ró¿ne k¹ty do zad3 lab2
        pr1.RysLinie(renderer, 50, 1, 50, 40);

        //zad5 lab2 - lineSegment
        //rysowanie odcinka przy pomocy Point2D
        line.Draw(renderer, true);
        // Odczytanie wspó³rzêdnych poszczególnych koñców odcinka
        Point2D start = line.GetStartPoint();
        Point2D end = line.GetEndPoint();
        /*koniec rysowania do linesegment*/ 

        /* Wypisanie wspó³rzêdnych poszczególnych koñców odcinka ale nie w petli zrobic
        //int startX, startY, endX, endY;
        //start.print_xy(startX, startY);
        //end.print_xy(endX, endY);
        //std::cout << "Start point: x=" << startX << ", y=" << startY << std::endl;
        //std::cout << "End point: x=" << endX << ", y=" << endY << std::endl;
        */

        /*modyfikacja odcinka do lineSegment*/
        // Modyfikacja wspó³rzêdnych poszczególnych koñców odcinka
        start.zmien_punkt(1, 50);
        end.zmien_punkt(799, 50);
        // Ustawienie zmodyfikowanych punktów w odcinku
        line.SetStartPoint(start);
        line.SetEndPoint(end);
        //rysowanie nowego odcinka
        line.Draw(renderer, true);
        /*koniec zad5 lab2 - lineSegment*/

        pr1.Otwarta(renderer, nazwa);
      
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }

        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    point.print_xy(p1.x, p1.y);
}

void Engine::MovementHandle()
{
    if (event.type == SDL_KEYDOWN)
    {
        if (SDLK_LEFT == event.key.keysym.sym)
            p1.MoveLeft();
        if (SDLK_RIGHT == event.key.keysym.sym)
            p1.MoveRight();
    }
}

Engine::~Engine()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
