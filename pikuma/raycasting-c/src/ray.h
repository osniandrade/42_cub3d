#ifndef RAY_H
#define RAY_H

#include <stdbool.h>
#include <limits.h>
#include "defs.h"
#include "graphics.h"
#include "player.h"
#include "utils.h"

typedef struct {
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    bool wasHitVertical;
    int wallHitContent;
} rays_t;

extern rays_t rays[NUM_RAYS];

void castRay(float rayAngle, int stripId);
void castAllRays(void);
void renderMapRays(void);

#endif