#ifndef SPRITE_H
#define SPRITE_H

#include "graphics.h"
#include "player.h"
#include "textures.h"
#include "defs.h"

typedef struct {
    float x;
    float y;
    float distance;
    float angle;
    int texture;
} sprite_t;

void renderSpriteProjection(void);
void renderMapSprites(void);

#endif