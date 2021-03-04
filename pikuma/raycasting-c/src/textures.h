#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>
#include <stdio.h>
#include "defs.h"
#include "upng.h"

#define NUM_TEXTURES 14

upng_t* textures[NUM_TEXTURES];

void loadTextures(void);
void freeTextures(void);

#endif