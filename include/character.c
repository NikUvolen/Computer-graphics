#include <GL/gl.h>
#include <winuser.h>
#include <stdbool.h>

#include "../headers/character.h"
#include "../headers/texturing.h"

const int WINDOW_HEIGHT = 840;

void setGravity(Character *chrt)
{
    
    if (chrt->velocityY < 0)
    {
        chrt->inAir = true;
    }
    if (chrt->inAir == false)
    {
        chrt->velocityX *= 0.8f;              //пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ?
        chrt->velocityY *= 0.8f;
    }

    chrt->posX += chrt->velocityX;         //пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    chrt->posY += chrt->velocityY;

    chrt->velocityY -= 9.8f;    
}

Character* initCharacter(float x, float y, unsigned int sprite) {
    Character* character = malloc(sizeof(Character));

    character->posX = x;
    character->posY = y;
    character->width = 100.0f;
    character->height = 100.0f;

    character->spriteSheet = sprite;

    character->turnedAround = false;
    character->inAir = true;
    character->animation = 2;
    character->frame = 0;
    character->velocityX = 0;
    character->velocityY = 0;
};

void drawCharacter(Character *chrt) {
    float characterPosX = chrt->posX - chrt->width * 0.5f;
    float characterPosY = WINDOW_HEIGHT - chrt->posY - chrt->height;

    // setting character spriteList
    float vertices[] = {
        characterPosX + chrt->width, characterPosY + chrt->height, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.1f + 0.1f * chrt->frame, 0.333333f * chrt->animation,

        characterPosX + chrt->width, characterPosY, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.1f + 0.1f * chrt->frame,  0.333333f * (chrt->animation - 1),

        characterPosX, characterPosY, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f + 0.1f * chrt->frame,   0.333333f * (chrt->animation - 1),

        characterPosX, characterPosY + chrt->height, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f + 0.1f * chrt->frame,   0.333333f * chrt->animation
    };

    if (chrt->turnedAround) {
        vertices[0] = vertices[8] -= chrt->width;
        vertices[16] = vertices[24] += chrt->width;
    }

    //_setGravity(chrt);

    renderImageFromMatrix(vertices, chrt->spriteSheet);

    chrt->frame += 1;
}

void changeAnimation(Character *chrt, int animNum) {
    if (chrt->animation != animNum) {
        chrt->animation = animNum;
        chrt->frame = 0;
    }
}

void addVelocity(Character *chrt, float horizontal, float vertical)
{
    chrt->velocityX += horizontal;
    chrt->velocityY += vertical;
}

void moveController (Character *chrt) {
    if (chrt->inAir) {
        changeAnimation(chrt, 1);
    }
    else if (GetKeyState(VK_LEFT)<0) {
        addVelocity(chrt, -10.0f, 0.0f);
        chrt -> turnedAround = true;
        changeAnimation(chrt, 2);

    }
    else if(GetKeyState(VK_RIGHT)<0) {
        addVelocity(chrt, 10.0f, 0.0f);
        chrt -> turnedAround = false;
        changeAnimation(chrt, 2);
    }
    else {
        changeAnimation(chrt, 3);
    }

    if (GetKeyState(VK_UP)<0 && chrt->inAir != true) {
        addVelocity(chrt, 0.0f, 80.0f);
        chrt -> inAir = true;
    }
    if (GetKeyState(VK_DOWN)<0 && chrt->inAir) {
        addVelocity(chrt, 0.0f, -100.0f);
    }
}
