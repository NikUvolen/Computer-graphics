#ifndef TEXTURING_H
#define TEXTURING_H
#include "texturing.h"

void initTexture(char* path, unsigned int *texture);
void renderImage(float width, float height, float xPos, float yPos, unsigned int texture, int isGround, float screenHight);
void renderImageFromMatrix (float vertices[], unsigned int texture);


#endif TEXTURING_H
