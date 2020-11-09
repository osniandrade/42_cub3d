const TILE_SIZE = 32;
const MAP_NUM_ROWS = 11;
const MAP_NUM_COLS = 15;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

const FOV_ANGLE = 60 * (Math.PI / 180);

const WALL_STRIP_WIDTH = 5;
const NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

const MINIMAP_SCALE_FACTOR = 0.2;

class Map {
  constructor() {
      this.grid = [
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
          [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
          [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
          [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
          [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
          [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
          [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
          [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
          [1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
          [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
      ];
  }
  render() {
      for (var i = 0; i < MAP_NUM_ROWS; i++) {
          for (var j = 0; j < MAP_NUM_COLS; j++) {
              var tileX = j * TILE_SIZE;
              var tileY = i * TILE_SIZE;
              var tileColor = this.grid[i][j] == 1 ? "#222" : "#fff";
              stroke("#222");
              fill(tileColor);
              rect(
                tileX * MINIMAP_SCALE_FACTOR, 
                tileY * MINIMAP_SCALE_FACTOR, 
                TILE_SIZE * MINIMAP_SCALE_FACTOR, 
                TILE_SIZE * MINIMAP_SCALE_FACTOR
              );
          }
      }
  }
  hasWallAt(x, y) {
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
      return true;
    }
    var mapGridIndexX = Math.floor(x / TILE_SIZE);
    var mapGridIndexY = Math.floor(y / TILE_SIZE);
    return this.grid[mapGridIndexY][mapGridIndexX] != 0 ? true : false;
  }
}

class Player {
  constructor() {
    this.x = WINDOW_WIDTH / 2;
    this.y = WINDOW_HEIGHT / 2;
    this.radius = 3;
    this.turnDirection = 0;  // -1 if left, +1 if right
    this.walkDirection = 0;  // -1 if back, +1 if front
    this.rotationAngle = Math.PI / 2;
    this.moveSpeed = 2.0;
    this.rotationSpeed = 2 * (Math.PI / 180);  // 2 degrees per frame
  }
  render() {
    noStroke();
    fill("blue");
    circle(
      this.x * MINIMAP_SCALE_FACTOR, 
      this.y * MINIMAP_SCALE_FACTOR, 
      this.radius * MINIMAP_SCALE_FACTOR
    );
    stroke("blue");
    line(
      this.x * MINIMAP_SCALE_FACTOR, 
      this.y * MINIMAP_SCALE_FACTOR,
      (this.x + Math.cos(this.rotationAngle) * 20) * MINIMAP_SCALE_FACTOR,
      (this.y + Math.sin(this.rotationAngle) * 20) * MINIMAP_SCALE_FACTOR
    );
  }
  update() {
    // atualiza posição do player baseado em turnDirection e walkDirection
    this.rotationAngle += this.turnDirection * this.rotationSpeed;

    var moveStep = this.walkDirection * this.moveSpeed;
    
    var newPlayerX = this.x + Math.cos(this.rotationAngle) * moveStep;
    var newPlayerY = this.y + Math.sin(this.rotationAngle) * moveStep;

    // só atualiza a posição se não houver parede
    if (!grid.hasWallAt(newPlayerX, newPlayerY)) {
      this.x = newPlayerX;
      this.y = newPlayerY;
    }
  }
}

class Ray {
  constructor(rayAngle) {
    this.rayAngle = normalizeAngle(rayAngle);
    this.wallHitX = 0;
    this.wallHitY = 0;
    this.distance = 0;
    this.wasHitVertical = false;

    this.isRayFacingDown = ((this.rayAngle > 0) && (this.rayAngle < Math.PI));
    this.isRayFacingUp = !this.isRayFacingDown;
    this.isRayFacingRight = this.rayAngle < (Math.PI * 0.5) || this.rayAngle > (Math.PI * 1.5);
    this.isRayFacingLeft = !this.isRayFacingRight;
  }
  render() {
    stroke("rgba(255,0,0,0.3)");
    line(player.x * MINIMAP_SCALE_FACTOR, 
         player.y * MINIMAP_SCALE_FACTOR,
         this.wallHitX * MINIMAP_SCALE_FACTOR,
         this.wallHitY * MINIMAP_SCALE_FACTOR);
  }
  cast() {
    var xstep, ystep;
    var xintercept, yintercept;

    //////////////////////////////////////////////////
    // CÓDIGO DE INTERSECÇÃO HORIZONTAL DOS RAIOS
    //////////////////////////////////////////////////
    var foundHorzWallHit = false;
    var horzWallHitX = 0;
    var horzWallHitY = 0;

    // encontrar a coord y da intersecção horizontal mais próxima na grid
    yintercept = Math.floor(player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += this.isRayFacingDown ? TILE_SIZE : 0;

    // encontrar a coord x da intersecção horizontal mais próxima na grid
    xintercept = player.x + (yintercept - player.y) / Math.tan(this.rayAngle);

    // calcular incremento para xstep e ystep
    ystep = TILE_SIZE;
    ystep *= this.isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / Math.tan(this.rayAngle);
    xstep *= (this.isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (this.isRayFacingRight && xstep < 0) ? -1 : 1;

    var nextHorzTouchX = xintercept;
    var nextHorzTouchY = yintercept;

    // incrementar xstep e ystep até achar uma parede
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
      if (grid.hasWallAt(nextHorzTouchX, nextHorzTouchY - (this.isRayFacingUp ? 1 : 0))) {
        foundHorzWallHit = true;
        horzWallHitX = nextHorzTouchX;
        horzWallHitY = nextHorzTouchY;

        break;
      } else {
        nextHorzTouchX += xstep;
        nextHorzTouchY += ystep;
      }
    }

    //////////////////////////////////////////////////
    // CÓDIGO DE INTERSECÇÃO VERTICAL DOS RAIOS
    //////////////////////////////////////////////////
    var foundVertWallHit = false;
    var vertWallHitX = 0;
    var vertWallHitY = 0;

    // encontrar a coord x da intersecção vertical mais próxima na grid
    xintercept = Math.floor(player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += this.isRayFacingRight ? TILE_SIZE : 0;

    // encontrar a coord x da intersecção vertical mais próxima na grid
    yintercept = player.y + (xintercept - player.x) * Math.tan(this.rayAngle);

    // calcular incremento para xstep e ystep
    xstep = TILE_SIZE;
    xstep *= this.isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * Math.tan(this.rayAngle);
    ystep *= (this.isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (this.isRayFacingDown && ystep < 0) ? -1 : 1;

    var nextVertTouchX = xintercept;
    var nextVertTouchY = yintercept;
    
    // incrementar xstep e ystep até achar uma parede
    while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) {
      if (grid.hasWallAt(nextVertTouchX - (this.isRayFacingLeft ? 1 : 0), nextVertTouchY)) {
        foundVertWallHit = true;
        vertWallHitX = nextVertTouchX;
        vertWallHitY = nextVertTouchY;
        break;
      } else {
        nextVertTouchX += xstep;
        nextVertTouchY += ystep;
      }
    }

    // calcular as duas distancias (horizontal e vertical) e escolher a menor
    var horzHitDistance = (foundHorzWallHit) 
      ? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
      : Number.MAX_VALUE;
    var vertHitDistance = (foundVertWallHit) 
      ? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
      : Number.MAX_VALUE;
    
    if (horzHitDistance < vertHitDistance) {
      this.wallHitX = horzWallHitX;
      this.wallHitY = horzWallHitY;
      this.distance = horzHitDistance;
      this.wasHitVertical = false;
    } else {
      this.wallHitX = vertWallHitX;
      this.wallHitY = vertWallHitY;
      this.distance = vertHitDistance;
      this.wasHitVertical = true;
    }
  }
}

var grid = new Map();
var player = new Player();
var rays = [];

function keyPressed() {
  if (keyCode == UP_ARROW) {
    player.walkDirection = +1;
  } else if (keyCode == DOWN_ARROW) {
    player.walkDirection = -1;
  } else if (keyCode == RIGHT_ARROW) {
    player.turnDirection = +1;
  } else if (keyCode == LEFT_ARROW) {
    player.turnDirection = -1;
  }
}

function keyReleased() {
  if (keyCode == UP_ARROW) {
    player.walkDirection = 0;
  } else if (keyCode == DOWN_ARROW) {
    player.walkDirection = 0;
  } else if (keyCode == RIGHT_ARROW) {
    player.turnDirection = 0;
  } else if (keyCode == LEFT_ARROW) {
    player.turnDirection = 0;
  }
}

function castAllRays() {
  // inicializar primeiro raio subtraindo metade do FOV
  var rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

  rays = [];

  // loop por cada coluna
  for (var col = 0; col < NUM_RAYS; col++) {
    var ray = new Ray(rayAngle);
    ray.cast();
    rays.push(ray);

    rayAngle += FOV_ANGLE / NUM_RAYS;
  }

}

function render3DProjectedWalls() {
  // loop por todos os rays no array
  for (var i = 0; i < NUM_RAYS; i++) {
    var ray = rays[i];

    var correctWallDistance = ray.distance * Math.cos(ray.rayAngle - player.rotationAngle);
    // calcula a distancia pro plano de projeção
    var distanceProjectionPlane = (WINDOW_WIDTH / 2) / Math.tan(FOV_ANGLE / 2);

    // altura da coluna da parede
    var wallStripHeight = (TILE_SIZE / correctWallDistance) * distanceProjectionPlane; 

    // calcula a transparencia baseado na distancia da parede
    //var alpha = 150.0 / correctWallDistance;
    var alpha = 1.0;
    var color = (ray.wasHitVertical) ? 255 : 180;
    //console.log(color);
  
    //fill("rgba(255, 255, 255, " + alpha + ")");
    fill("rgba(" + color + "," + color + "," + color + "," + alpha + ")");
    noStroke();
    rect(
      i * WALL_STRIP_WIDTH,
      (WINDOW_HEIGHT / 2) - (wallStripHeight / 2),
      WALL_STRIP_WIDTH,
      wallStripHeight
    );
  }
}

function normalizeAngle(angle) {
  // força o angulo a ficar sempre entre 0 e 2 PI
  angle = angle % (2 * Math.PI);
  if (angle < 0) {
    angle = (2 * Math.PI) + angle;
  }
  return angle;
}

function distanceBetweenPoints(x1, y1, x2, y2) {
  // calcula a distancia entre dois pontos usando pitágoras (hipotenusa)
  return Math.sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

function setup() {
    // inicializa os objetos
    createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT)
}

function update() {
    // atualiza todos os objetos antes de renderizar o proximo frame
    player.update();
    castAllRays();
}

function draw() {
    // renderiza todos os objetos frame a frame
    clear("#212121");
    update();
    render3DProjectedWalls();
    grid.render();
    for (ray of rays) {
      ray.render();
    }
    player.render();
    
}