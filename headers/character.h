#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdbool.h>

typedef struct
{
    float height;
    float width;
    float posX;
    float posY;
    bool turnedAround;
    bool inAir;
    unsigned int spriteSheet;
    int animation;
    int frame;
    float velocityX;
    float velocityY;

} Character;

Character* initCharacter(float x, float y, unsigned int sprite);
void drawCharacter(Character *chrt);
void changeAnimation (Character *chrt, int animationNumber);
void addVelocity(Character *chrt, float horizontal, float vertical);
void moveController (Character *chrt);
void setGravity(Character *chrt);

#endif CHARACTER_H
