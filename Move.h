#ifndef func
#define func

void right( SDL_Rect *square, int speed)
{
    square->x += speed;
}
void left(SDL_Rect* square, int speed)
{
    square->x -= speed;
}
void up(SDL_Rect* square, int speed)
{
    square->y -= speed;
}
void down(SDL_Rect* square, int speed)
{
    square->y += speed;
}


#endif