#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "character.h"

void collisionCheck(Character *chrt, float xSizeGround, float ySizeGround, float groundsCoords[][2], int numberOfGrounds, float colliders[][4], int numberOfColliders);

#endif COLLISION_H
