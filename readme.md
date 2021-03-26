## **CUB 3D**

*This project is inspired by the world-famous eponymous 90’s game, which
was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to
make a dynamic view inside a maze, in which you’ll have to find your way.*

## HOW TO USE
You'll need the basic tools to compile C code. All non-standard libraries included in this project are inside the main folder.

### RUN
-` make debug; make run`

### COMMAND
- W, A, S, D - walk
- Q, E - turn
- ESC - quit

### MAP
The map file includes the path to textures used in the graphics rendering. Files must me 64x64 pixels and "xpm" type. These rules also work for the sprite texture.

Only 4 wall textures and a single sprite texture is supported for now.

The map is comprised of the following characters:
- 1 - wall
- 0 - path
- N, S, W, E - player initial looking direction
- 2 - sprite position (a single sprite is supported for now)

The map must be sorrounded by 1's, without open ends. You can edit the map.cub file and change the map as you will following the above rules.

*This is a work in progress. There are still some memory leaks being corrected.*