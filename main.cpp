#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cmath>
#include "Structs.h"
#include "Funcs.h"
#include "PlayerController.h"

#define WHITE SDL_Color{255, 255, 255, 255}
#define BLACK SDL_Color{0, 0, 0, 255}
#define BLUE SDL_Color{0, 0, 255, 255}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("[Name]", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 400, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_Event event;

    bool quit = false;
    bool paused = false;

    Vector2 MousePos;

    PlayerController Player;
    Player.object = {"Player", {400, 200}, {20, 40}, WHITE};

    Object Floor = {"Floor", {400, 375}, {800, 50}, BLUE};
    Object Wall = {"Wall", {400, 300}, {25, 100}, BLUE};

    vector<Object> CollideObj = {Floor, Wall};
    Uint64 Now = SDL_GetPerformanceCounter();
    Uint64 Last = 0;
    float deltaTime = 0;
    while(!quit)
    {
        Last = Now;
        Now = SDL_GetPerformanceCounter();
        deltaTime = (double)((Now - Last)*100 / (double)SDL_GetPerformanceFrequency());
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

                
        for(int i = 0; i < CollideObj.size(); i++)
        {
            RenderDrawObject(renderer, CollideObj[i]);
            Object temp;
            temp.Scale = {Player.Velocity.x, Player.object.Scale.y};
            temp.Position = Player.object.Position;
            if(IsColliding(CollideObj[i], temp))
            {
                Player.Collide(CollideObj[i], {Player.Velocity.x, 0});
            }
            temp.Scale = {Player.object.Scale.x, Player.Velocity.y};
            if(IsColliding(CollideObj[i], temp))
            {
                Player.Collide(CollideObj[i], {0, Player.Velocity.y});
            }
        }
        Player.Update();
        RenderDrawObject(renderer, Player.object);

        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}