#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Structs.h"

using namespace std;

vector<SDL_Rect> CreateMapCollision(char *path, int Scale)
{
    vector<SDL_Rect> MapCollision;
    SDL_Surface *mapSurface = IMG_Load(path);

    const Uint8 Bpp = mapSurface->format->BytesPerPixel;
    Uint8 *pPixel;
    Uint32 PixelData;
    SDL_Color color = {0, 0, 0, 0};
    // cout << (int)color.a;
    for(int i = 0; i < mapSurface->h; i++)
    {
        for(int j = 0; j < mapSurface->w; j++)
        {
            pPixel = (Uint8*)mapSurface->pixels + i * mapSurface->pitch + j * Bpp;
            PixelData = *(Uint32*)pPixel;
            SDL_GetRGBA(PixelData, mapSurface->format, &color.r, &color.g, &color.b, &color.a);
            if((int)color.a != 0)
            {
                MapCollision.push_back({j*Scale, i*Scale, Scale, Scale});
            }
        }
    }
    return MapCollision;
}

bool IsColliding(Object a, Object b)
{
    if(a.Position.x + a.Scale.x > b.Position.x && a.Position.x < b.Position.x + b.Scale.x && a.Position.y + a.Scale.y > b.Position.y && a.Position.y < b.Position.y + b.Scale.y)
    {
        return true;
    }
    return false;
}
bool WillCollide(Object a, Object b, Vector2 NextPos)
{
    if(a.Position.x + a.Scale.x + NextPos.x > b.Position.x && a.Position.x + NextPos.x < b.Position.x + b.Scale.x && a.Position.y + a.Scale.y + NextPos.y > b.Position.y && a.Position.y + NextPos.y < b.Position.y + b.Scale.y)
    {
        return true;
    }
    return false;
}
bool PointCollide(Object a, Vector2 point)
{
    if(point.x > a.Position.x && point.x < a.Position.x + a.Scale.x && point.y > a.Position.y && point.y < a.Position.y + a.Scale.y)
    {
        return true;
    }
    return false;
}
bool BoxCast(Object Obj, Vector2 Dir, float Magnitude, vector<Object> Mask)
{
    Object temp = Obj;
    for(int i = 0; i < Mask.size(); i++)
    {
        for(int j = 0; j < Magnitude; j++)
        {
            temp.Position = temp.Position + Dir * j;
            if(IsColliding(temp, Mask[i]))
            {
                return true;
            }
        }
    }
    return false;
}
// void DrawObject(SDL_Renderer *renderer, Object obj, CameraController Camera)
// {
//     SDL_SetRenderDrawColor(renderer, obj.Color.r, obj.Color.g, obj.Color.b, obj.Color.a);
//     SDL_Rect DrawRect;
//     DrawRect.x = obj.Position.x - Camera.Position.x;
//     DrawRect.y = obj.Position.y - Camera.Position.y;
//     DrawRect.w = obj.Scale.x;
//     DrawRect.h = obj.Scale.y;
//     SDL_RenderFillRect(renderer, &DrawRect);
// }
void RenderDrawObject(SDL_Renderer *renderer, Object obj)
{
    SDL_Rect DrawRect;
    DrawRect.x = obj.Position.x;
    DrawRect.y = obj.Position.y;
    DrawRect.w = obj.Scale.x;
    DrawRect.h = obj.Scale.y;
    SDL_SetRenderDrawColor(renderer, obj.Color.r, obj.Color.g, obj.Color.b, obj.Color.a);
    SDL_RenderFillRect(renderer, &DrawRect);
}
void blitMap(SDL_Renderer *renderer, char *imgSrc, float x, float y, float ScaleOffest)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_Texture *MapTexture = IMG_LoadTexture(renderer, imgSrc);
    SDL_QueryTexture(MapTexture, NULL, NULL, &dest.w, &dest.h);
    dest.w = dest.w*ScaleOffest;
    dest.h = dest.h*ScaleOffest;
    SDL_RenderCopy(renderer, MapTexture, NULL, &dest);
    SDL_DestroyTexture(MapTexture);
}