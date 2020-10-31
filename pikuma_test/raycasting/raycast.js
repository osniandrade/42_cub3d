const TILE_SIZE = 32;
const MAP_NUM_ROWS = 11;
const MAP_NUM_COLS = 15;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

const FOV_ANGLE = 60 * (Math.PI / 180);

const WALL_STRIP_WIDTH = 30;
const NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

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
              rect(tileX, tileY, TILE_SIZE, TILE_SIZE);
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
    fill("red");
    circle(this.x, this.y, this.radius);
    // stroke("red");
    // line(
    //   this.x, 
    //   this.y,
    //   this.x + Math.cos(this.rotationAngle) * 20,
    //   this.y + Math.sin(this.rotationAngle) * 20
    // );
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

    this.isRayFacingDown = ((this.rayAngle > 0) && (this.rayAngle < Math.PI));
    this.isRayFacingUp = !this.isRayFacingDown;
    this.isRayFacingRight = this.rayAngle < (Math.PI * 0.5) || this.rayAngle > (Math.PI * 1.5);
    this.isRayFacingLeft = !this.isRayFacingRight;
  }
  render() {
    stroke("rgba(255,0,0,0.3)");
    line(player.x, 
         player.y, 
         player.x + Math.cos(this.rayAngle) * 30, 
         player.y + Math.sin(this.rayAngle) * 30);
  }
  cast() {
    var xstep, ystep;
    var xintercept, yintercept;
    
    console.log("isRayFacingRight?", this.isRayFacingRight);

    //////////////////////////////////////////////////
    // CÓDIGO DE INTERSECÇÃO HORIZONTAL DOS RAIOS
    //////////////////////////////////////////////////

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
  var columnId = 0;

  // inicializar primeiro raio subtraindo metade do FOV
  var rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

  rays = [];

  // loop por cada coluna
  //for (var i = 0; i < NUM_RAYS; i++) {
  for (var i = 0; i < 1; i++) {
    var ray = new Ray(rayAngle);
    ray.cast(columnId);
    rays.push(ray);

    rayAngle += FOV_ANGLE / NUM_RAYS;

    columnId++;
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
    update();
    grid.render();
    for (ray of rays) {
      ray.render();
    }
    player.render();
}