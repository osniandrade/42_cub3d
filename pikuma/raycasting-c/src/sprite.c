#include "sprite.h"

#define NUM_SPRITES 1

static sprite_t sprites[NUM_SPRITES] = {
    {.x = 640, .y = 630, .texture = 9}  // barrel
};

void renderMapSprites(void){
    for (int i = 0; i < NUM_SPRITES; i++) {
        drawRect(
            sprites[i].x * MINIMAP_SCALE_FACTOR,
            sprites[i].y * MINIMAP_SCALE_FACTOR, 
            2, 
            2, 
            0xFF00FFFF);
    }
}

void renderSpriteProjection(void) {
    // TODO
}

