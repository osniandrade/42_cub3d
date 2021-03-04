#include "wall.h"

void renderWallProjection() {
    for (int x = 0; x < NUM_RAYS; x++) {
        float perpDistance = rays[x].distance * cos(rays[x].rayAngle - player.rotationAngle);
        float projectedWallHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;
        
        int wallStripHeight = (int)projectedWallHeight;

        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

        // render wall column from wallTopPixel to wallBottomPixel
        for (int y = 0; y < wallTopPixel; y++) {
            drawPixel(x, y, 0xFF444444);
        }

        int textureOffsetX;
        if (rays[x].wasHitVertical) {
            textureOffsetX = (int)rays[x].wallHitY % TILE_SIZE;
        } else {
            textureOffsetX = (int)rays[x].wallHitX % TILE_SIZE;
        }

        // get the correct texture id number from map content
        int texNum = rays[x].wallHitContent - 1;
        int texture_width = wallTextures[texNum].width;
        int texture_height = wallTextures[texNum].height;

        for (int y = wallTopPixel; y < wallBottomPixel; y++) {
            // calculate textureOffsetY
            int distanceFromTop = (y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2));
            int textureOffsetY = distanceFromTop * ((float)texture_height / wallStripHeight);

            // set the color of the wall based on the color from the texture
            color_t texelColor = wallTextures[texNum].texture_buffer[(texture_width * textureOffsetY) + textureOffsetX];
            if (rays[x].wasHitVertical) {
                changeColorIntensity(&texelColor, 0.7);
            }
            drawPixel(x, y, texelColor);
        }

        for (int y = wallBottomPixel; y < wallBottomPixel; y++) {
            drawPixel(x, y, 0xFF888888);
        }
    }
}

void changeColorIntensity(color_t* color, float factor) {
    color_t a = (*color & 0xFF000000);
    color_t r = (*color & 0x00FF0000) * factor;
    color_t g = (*color & 0x0000FF00) * factor;
    color_t b = (*color & 0x000000FF) * factor;

    *color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}