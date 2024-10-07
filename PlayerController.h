#include <SDL.h>
#include <cmath>
#include <iostream>
#include "Structs.h"
class PlayerController
{
    private:
        
        Uint64 Now = SDL_GetPerformanceCounter();
        Uint64 Last = 0;
        float deltaTime = 0;
        float gravity = 9;
        float SpeedCap = 8;
        float Floaty = 5;
        float Slippery = 50;
        Vector2 TargetVelocity = {0, 0};
        Vector2 Velocity = {0, 0};
        vector<Object> CollideObj;
        bool grounded = false;
    public:
        Object object;
        Vector2 MoveDirection = {0, 0};

        void Start(vector<Object> temp)
        {
            CollideObj = temp;
            object.Position = object.Position + object.Position.Normalized() * 0.1;
        }
        void Update()
        {
            Last = Now;
            Now = SDL_GetPerformanceCounter();
            deltaTime = (double)((Now - Last)*100 / (double)SDL_GetPerformanceFrequency());

            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])
            {
                MoveDirection.x = -1;
            }
            else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])
            {
                MoveDirection.x = 1;
            }
            else
            {
                MoveDirection.x = 0;
            }
            // if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])
            // {
            //     if(!jump)
            //     {
            //         jump = true;
            //         jumping = true;
            //     }
            // }
            // else
            // {
            //     jump = false;
            // }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W] && grounded)
            {
                Velocity.y = -20;
                grounded = false;
            }
            // else if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])
            // {
            //     MoveDirection.y = 1;
            // }
            // else
            // {
            //     MoveDirection.y = 0;
            // }
            Floaty = 5;
            if(Velocity.y < 0)
            {
                Floaty = 15;
            }
            MoveDirection = MoveDirection.Normalized();

            TargetVelocity.x = MoveDirection.x * SpeedCap;

            Velocity.x += (TargetVelocity.x - Velocity.x)/Slippery;
            Velocity.y += (gravity - Velocity.y)/Floaty*deltaTime;

            // cout << CurrentSpeed << endl;
            for(int i = 0; i < CollideObj.size(); i++)
            {
                if(WillCollide(object, CollideObj[i], {0, Velocity.y}))
                {
                    Collide({0, Velocity.y});
                }
                if(WillCollide(object, CollideObj[i], {Velocity.x, 0}))
                {
                    Collide({Velocity.x, 0});
                }
            }
            object.Position = object.Position + Velocity*deltaTime;
        }
        void Collide(Vector2 Direction)
        {
            Velocity = Velocity - Direction;
            if(Direction.y > 0)
            {
                grounded = true;
            }
        }
};