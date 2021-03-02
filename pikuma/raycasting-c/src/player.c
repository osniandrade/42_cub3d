#include "player.h"

player_t player = {
    .x = WINDOW_WIDTH / 2,
    .y = WINDOW_HEIGHT / 2,
    .width = 1,
    .height = 1,
    .turnDirection = 0,
    .walkDirection = 0,
    .rotationAngle = PI / 2,
    .walkSpeed = 80,
    .turnSpeed = 45 * (PI / 180)
};

void movePlayer(float deltaTime) {
    player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;
    float moveStep = player.walkDirection * player.walkSpeed * deltaTime;

    float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
    float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;

    if (!mapHasWallAt(newPlayerX, newPlayerY)) {
        player.x = newPlayerX;
        player.y = newPlayerY;
    } 
}

void renderPlayer() {
    drawRect(
        MINIMAP_SCALE_FACTOR * player.x,
        MINIMAP_SCALE_FACTOR * player.y,
        MINIMAP_SCALE_FACTOR * player.width,
        MINIMAP_SCALE_FACTOR * player.height,
        0xFFFFFFFF
    );
}
