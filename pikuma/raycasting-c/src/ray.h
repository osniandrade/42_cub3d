#ifndef RAY_H
#define RAY_H

#include <stdbool.h>
#include <limits.h>
#include "defs.h"
#include "graphics.h"
#include "player.h"

typedef struct {
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    bool wasHitVertical;
    int wallHitContent;
} rays_t;

extern rays_t rays[NUM_RAYS];

void normalizeAngle(float *angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
void castRay(float rayAngle, int stripId);
void castAllRays(void);
void renderMapRays(void);

#endif