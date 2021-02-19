#include <stdio.h>
#include <SDL2/SDL.h>
#include <limits.h>
#include "constants.h"
#include "textures.h"

struct Player {
    float x;
    float y;
    float width;
    float height;
    int turnDirection;  // -1 for left, +1 for right
    int walkDirection;  // -1 for back, +1 for front
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} player;

struct Ray {
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    int wasHitVertical;
    int isRayFacingUp;
    int isRayFacingDown;
    int isRayFacingLeft;
    int isRayFacingRight;
    int wallHitContent;
} rays[NUM_RAYS];

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 2, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 5, 0, 0, 0, 0, 0, 9, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5}
};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int isGameRunning = FALSE;
int ticksLastFrame = 0;

uint32_t* colorBuffer = NULL;
SDL_Texture* colorBufferTexture;
uint32_t* textures[NUM_TEXTURES];

int initializeWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL window. \n");
        return FALSE;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);  // -1 gets the default driver
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    return TRUE;
}

void destroyWindow() {
    freeWallTextures();
    free(colorBuffer);
    SDL_DestroyTexture(colorBufferTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void setup() {
    player.x = WINDOW_WIDTH / 2;
    player.y = WINDOW_HEIGHT / 2;
    player.width = 1;
    player.height = 1;
    player.turnDirection = 0;
    player.walkDirection = 0;
    player.rotationAngle = PI / 2;
    player.walkSpeed = 80;
    player.turnSpeed = 45 * (PI / 180);

    // allocate the total amount of bytes in memory to hold the colorBuffer
    colorBuffer = (uint32_t*) malloc( sizeof(uint32_t) * (uint32_t)WINDOW_WIDTH * (uint32_t)WINDOW_HEIGHT);

    // create an SDL_Texture to display the color buffer
    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );

    // asks uPNG library to decode all PNG files and loads the wallTextures to hold our colorbuffer
    loadWallTextures();
}

int mapHasWallAt(float x, float y) {
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return TRUE;
    }
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect playerRect = {
        MINIMAP_SCALE_FACTOR * player.x,
        MINIMAP_SCALE_FACTOR * player.y,
        MINIMAP_SCALE_FACTOR * player.width,
        MINIMAP_SCALE_FACTOR * player.height
    };
    SDL_RenderFillRect(renderer, &playerRect);

    SDL_RenderDrawLine(
        renderer,
        MINIMAP_SCALE_FACTOR * player.x,
        MINIMAP_SCALE_FACTOR * player.y,
        MINIMAP_SCALE_FACTOR * player.x + cos(player.rotationAngle) * 40,
        MINIMAP_SCALE_FACTOR * player.y + sin(player.rotationAngle) * 40
    );
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float normalizeAngle(float angle) {
    angle = remainder(angle, TWO_PI);
    if (angle < 0) {
        angle = TWO_PI + angle;
    }
    return angle;
}

void castRay(float rayAngle, int stripId) {
    rayAngle = normalizeAngle(rayAngle);

    int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;

    float xIntercept, yIntercept;
    float xStep, yStep;

    ////////////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ////////////////////////////////////////////////
    int foundHorzWallHit = FALSE;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallContent = 0;

    // find the y-coordinate of the closest horizontal grid intersection
    yIntercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
    yIntercept += isRayFacingDown ? TILE_SIZE : 0;
    
    // find the x-coordinate of the closest horizontal grid intersection
    xIntercept = player.x + (yIntercept - player.y) / tan(rayAngle);

    // calculate the increment xtesp and ystep
    yStep = TILE_SIZE;
    yStep *= isRayFacingUp ? -1 : 1;

    xStep = TILE_SIZE / tan(rayAngle);
    xStep *= (isRayFacingLeft && xStep > 0) ? -1 : 1;
    xStep *= (isRayFacingRight && xStep < 0) ? -1 : 1;

    float nextHorzTouchX = xIntercept;
    float nextHorzTouchY = yIntercept;

    //increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

        if (mapHasWallAt(xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = TRUE;
            break;
        } else {
            nextHorzTouchX += xStep;
            nextHorzTouchY += yStep;
        }
    }

    ////////////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ////////////////////////////////////////////////
    int foundVertWallHit = FALSE;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    int vertWallContent = 0;

    // find the x-coordinate of the closest vertical grid intersection
    xIntercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
    xIntercept += isRayFacingRight ? TILE_SIZE : 0;
    
    // find the y-coordinate of the closest vertical grid intersection
    yIntercept = player.y + (xIntercept - player.x) * tan(rayAngle);

    // calculate the increment xstep and ystep
    xStep = TILE_SIZE;
    xStep *= isRayFacingLeft ? -1 : 1;

    yStep = TILE_SIZE * tan(rayAngle);
    yStep *= (isRayFacingUp && yStep > 0) ? -1 : 1;
    yStep *= (isRayFacingDown && yStep < 0) ? -1 : 1;

    float nextVertTouchX = xIntercept;
    float nextVertTouchY = yIntercept;

    //increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;

        if (mapHasWallAt(xToCheck, yToCheck)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = TRUE;
            break;
        } else {
            nextVertTouchX += xStep;
            nextVertTouchY += yStep;
        }
    }

    // calculate both horizontal and vertical hit distance and choose the smallest one
    float horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY) : FLT_MAX;
    float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY) : FLT_MAX;

    if (vertHitDistance < horzHitDistance) {
        rays[stripId].distance = vertHitDistance;
        rays[stripId].wallHitX = vertWallHitX;
        rays[stripId].wallHitY = vertWallHitY;
        rays[stripId].wallHitContent = vertWallContent;
        rays[stripId].wasHitVertical = TRUE;
    } else {
        rays[stripId].distance = horzHitDistance;
        rays[stripId].wallHitX = horzWallHitX;
        rays[stripId].wallHitY = horzWallHitY;
        rays[stripId].wallHitContent = horzWallContent;
        rays[stripId].wasHitVertical = FALSE;
    }
    rays[stripId].rayAngle = rayAngle;
    rays[stripId].isRayFacingDown = isRayFacingDown;
    rays[stripId].isRayFacingUp = isRayFacingUp;
    rays[stripId].isRayFacingLeft = isRayFacingLeft;
    rays[stripId].isRayFacingRight = isRayFacingRight;
}

void castAllRays() {
    for (int col = 0; col < NUM_RAYS; col++) {
        float rayAngle = player.rotationAngle + atan((col - NUM_RAYS/2) / DIST_PROJ_PLANE);
        castRay(rayAngle, col);
    }
}

void renderMap() {
    for (int i = 0; i < MAP_NUM_ROWS; i++) {
        for (int j = 0; j < MAP_NUM_COLS; j++) {
            int tileX = j * TILE_SIZE;
            int tileY = i * TILE_SIZE;
            int tileColor = map[i][j] != 0 ? 255 : 0;

            SDL_SetRenderDrawColor(renderer, tileColor, tileColor, tileColor, 255);
            SDL_Rect mapTileRect = {
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR
            };
            SDL_RenderFillRect(renderer, &mapTileRect);
        }
    }
}

void renderRays() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < NUM_RAYS; i++) {
        SDL_RenderDrawLine(
            renderer,
            MINIMAP_SCALE_FACTOR * player.x,
            MINIMAP_SCALE_FACTOR * player.y,
            MINIMAP_SCALE_FACTOR * rays[i].wallHitX,
            MINIMAP_SCALE_FACTOR * rays[i].wallHitY
        );
    }
}

void processInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            isGameRunning = FALSE;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isGameRunning = FALSE;
            if (event.key.keysym.sym == SDLK_UP)
                player.walkDirection = +1;
            if (event.key.keysym.sym == SDLK_DOWN)
                player.walkDirection = -1;
            if (event.key.keysym.sym == SDLK_LEFT)
                player.turnDirection = -1;
            if (event.key.keysym.sym == SDLK_RIGHT)
                player.turnDirection = +1;
            break;
        }
        case SDL_KEYUP: {
            if (event.key.keysym.sym == SDLK_UP)
                player.walkDirection = 0;
            if (event.key.keysym.sym == SDLK_DOWN)
                player.walkDirection = 0;
            if (event.key.keysym.sym == SDLK_LEFT)
                player.turnDirection = 0;
            if (event.key.keysym.sym == SDLK_RIGHT)
                player.turnDirection = 0;
            break;
        }
    }
}

void update() {
    // compute how long we have until we reach the target frame time in miliseconds
    int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

    // only delay execution if we are running too fast
    if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH) {
        SDL_Delay(timeToWait);
    }
    
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f; // calculates DeltaTime

    ticksLastFrame = SDL_GetTicks();

    movePlayer(deltaTime);
    castAllRays();
}

void generate3DProjection() {
    for (int i = 0; i < NUM_RAYS; i++) {
        float perpDistance = rays[i].distance * cos(rays[i].rayAngle - player.rotationAngle);
        float projectedWallHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;
        
        int wallStripHeight = (int)projectedWallHeight;

        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

        // render wall column from wallTopPixel to wallBottomPixel
        for (int y = 0; y < wallTopPixel; y++) {
            colorBuffer[(WINDOW_WIDTH * y) + i] = 0xFF333333;
        }

        int textureOffsetX;
        //TODO: calculate textureOffsetX
        if (rays[i].wasHitVertical) {
            textureOffsetX = (int)rays[i].wallHitY % TILE_SIZE;
        } else {
            textureOffsetX = (int)rays[i].wallHitX % TILE_SIZE;
        }

        // get the correct texture id number from map content
        int texNum = rays[i].wallHitContent - 1;
        int texture_width = wallTextures[texNum].width;
        int texture_height = wallTextures[texNum].height;

        for (int y = wallTopPixel; y < wallBottomPixel; y++) {
            // calculate textureOffsetY
            int distanceFromTop = (y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2));
            int textureOffsetY = distanceFromTop * ((float)texture_height / wallStripHeight);

            // set the color of the wall based on the color from the texture
            uint32_t texelColor = wallTextures[texNum].texture_buffer[(texture_width * textureOffsetY) + textureOffsetX];
            colorBuffer[(WINDOW_WIDTH * y) + i] = texelColor;
        }

        for (int y = wallBottomPixel; y < wallBottomPixel; y++) {
            colorBuffer[(WINDOW_WIDTH * y) + i] = 0xFF777777;
        }
    }
}

void clearColorBuffer(uint32_t color) {
    for (int x = 0; x < WINDOW_WIDTH; x++) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            colorBuffer[(WINDOW_WIDTH * y) + x] = color;
        }
    }
}

void renderColorBuffer() {
    SDL_UpdateTexture(
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int)((uint32_t)WINDOW_WIDTH * sizeof(uint32_t))
    );
    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    generate3DProjection();

    renderColorBuffer();
    clearColorBuffer(0xFF000000);

    // displays the minimap
    renderMap();
    renderRays();
    renderPlayer();

    SDL_RenderPresent(renderer);
}

int main () {
    isGameRunning = initializeWindow();

    setup();

    while(isGameRunning) {
        processInput();
        update();
        render();
    }

    destroyWindow;

    return 0;
}