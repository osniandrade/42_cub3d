#include "sprite.h"

#define NUM_SPRITES 5

static sprite_t sprites[NUM_SPRITES] = {
    {.x = 640, .y = 630, .texture = 9}, // barrel
    {.x = 660, .y = 690, .texture = 9}, // barrel
    {.x = 350, .y = 600, .texture = 11},// table
    {.x = 300, .y = 400, .texture = 12}, // guard
    {.x = 900, .y = 100, .texture = 13} // armor
};

void renderMapSprites(void){
    for (int i = 0; i < NUM_SPRITES; i++) {
        drawRect(
            sprites[i].x * MINIMAP_SCALE_FACTOR,
            sprites[i].y * MINIMAP_SCALE_FACTOR, 
            2, 
            2, 
            (sprites[i].visible) ? 0xFF00FFFF : 0xFF444444
        );
    }
}

void renderSpriteProjection(void) {
    sprite_t visibleSprites[NUM_SPRITES];
    int numVisibleSprites = 0;

    // find the sprites that are visible
    for (int i = 0; i < NUM_SPRITES; i++) {
        float angleSpritePlayer = player.rotationAngle - atan2(sprites[i].y - player.y, sprites[i].x - player.x);
        
        // make sure the angle is always between 0 and 180
        if (angleSpritePlayer > PI)
            angleSpritePlayer -= TWO_PI;
        if (angleSpritePlayer < -PI)
            angleSpritePlayer += TWO_PI;
        angleSpritePlayer = fabs(angleSpritePlayer);

        // if sprite angle is less than half the FOV plus a small error margin
        const float EPSILON = 0.2;
        if (angleSpritePlayer < (FOV_ANGLE / 2) + EPSILON) {
            sprites[i].visible = true;
            sprites[i].angle = angleSpritePlayer;
            sprites[i].distance = distanceBetweenPoints(sprites[i].x, sprites[i].y, player.x, player.y);
            visibleSprites[numVisibleSprites] = sprites[i];
            numVisibleSprites++;
        } else {
            sprites[i].visible = false;
        }
    }
    
    // sort sprites by distance
    for (int i = 0; i < numVisibleSprites - 1; i++) {
        for (int j = i + 1; j < numVisibleSprites; j++) {
            if (visibleSprites[i].distance < visibleSprites[j].distance) {
                sprite_t temp = visibleSprites[i];
                visibleSprites[i] = visibleSprites[j];
                visibleSprites[j] = temp;
            }
        }
    }

    // rendering all visible sprites
    for (int i = 0; i < numVisibleSprites; i++) {
        sprite_t sprite = visibleSprites[i];

        // calculate the perpendicular distance of the sprite do avoid fisheye distortion
        float perpDistance = sprite.distance * cos(sprite.angle);

        // Calculate the sprite projected height (sprites are squared)
        float spriteHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;
        float spriteWidth = spriteHeight;

        // sprite top Y
        float spriteTopY = (WINDOW_HEIGHT / 2) - (spriteHeight / 2);
        spriteTopY = (spriteTopY < 0) ? 0 : spriteTopY;

        // sprite bottom Y
        float spriteBottomY = (WINDOW_HEIGHT / 2) + (spriteHeight / 2);
        spriteBottomY = (spriteBottomY > WINDOW_HEIGHT) ? WINDOW_HEIGHT : spriteBottomY;

        // Calculate the sprite X position in the projection plane
        float spriteAngle = atan2(sprite.y - player.y, sprite.x - player.x) - player.rotationAngle;
        float spriteScreenPosX = tan(spriteAngle) * DIST_PROJ_PLANE;

        // SpriteLeftX
        float spriteLeftX = (WINDOW_WIDTH / 2) + spriteScreenPosX - (spriteWidth / 2);

        // SpriteRightX
        float spriteRightX = spriteLeftX + spriteWidth;

        // query width and heigth of texture
        int textureWidth = upng_get_width(textures[sprite.texture]);
        int textureHeight = upng_get_height(textures[sprite.texture]);

        // Loop all the x and y values
        for (int x = spriteLeftX; x < spriteRightX; x++) {
            float texelWidth = (textureWidth / spriteWidth);
            int textureOffsetX = (x - spriteLeftX) * texelWidth;
            
            for (int y = spriteTopY; y < spriteBottomY; y++) {
                if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT) {
                    int distanceFromTop = y + (spriteHeight / 2) - (WINDOW_HEIGHT / 2);
                    int textureOffsetY = distanceFromTop * (textureHeight / spriteHeight);

                    color_t* spriteTextureBuffer = (color_t*)upng_get_buffer(textures[sprite.texture]);
                    color_t texelColor = spriteTextureBuffer[(textureWidth * textureOffsetY) + textureOffsetX];

                    if (sprite.distance < rays[x].distance &&  texelColor != 0xFFFF00FF) {
                        drawPixel(x, y, texelColor);
                    }
                }
            }
        }

    }
}

