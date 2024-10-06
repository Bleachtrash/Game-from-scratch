#include <SDL.h>
#include <cmath>
#include <iostream>
#include "Structs.h"
class PlayerController
{
    private:
        float AccelSpeed = 2;
        float SpeedCap = 15;
        float friction = 5;
        Uint64 Now = SDL_GetPerformanceCounter();
        Uint64 Last = 0;
        float deltaTime = 0;
        float gravity = 4;
    public:
        Object object;
        Vector2 Velocity = {0, 0};
        Vector2 Acceleration = {0, 0};
        Vector2 MoveDirection = {0, 0};
        Vector2 Middle = object.Position + object.Scale/2;
        bool jump = false;
        bool jumping = false;
        bool grounded = false;
        bool canJump = false;

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
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])
            {
                if(!jump)
                {
                    jump = true;
                    jumping = true;
                }
            }
            else
            {
                jump = false;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])
            {
                MoveDirection.y = 1;
            }
            else
            {
                MoveDirection.y = 0;
            }
            MoveDirection = MoveDirection.Normalized();

            gravity = 0; 
            friction = 4;
            // object.Position = object.Position + Vector2{30, 30} * deltaTime;

            Acceleration = (Velocity.Magnitude() < SpeedCap? MoveDirection * AccelSpeed : Vector2{0, 0});

            if(!grounded && jump && Velocity.y < 0)
            {
                gravity = 1.5;
                // cout << "HELLO??\n";
            }
            if(!grounded)
            {
                Velocity.y += Velocity.y< SpeedCap? gravity * deltaTime : 0;
                friction = 50;
            }
            if(grounded && jumping)
            {
                Velocity.y = -25;
                jumping = false;
                grounded = false;
            }

            object.Position = object.Position + Velocity * deltaTime;
            Velocity = Velocity + Acceleration * deltaTime;
            
            Velocity = Velocity - Velocity/friction*deltaTime;
        }
        void Collide(Object Collision, Vector2 Direction)
        {
            cout << GetDistance(object, Collision, Direction) << endl;
        }
};