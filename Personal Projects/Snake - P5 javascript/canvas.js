let snake;
let food;
let collision;
let scl = 10;
let height = window.innerHeight;
let width = window.innerWidth;
let cols = Math.floor(width / scl);
let rows = Math.floor(height / scl);
// let cols = 60;
// let rows = 60;

function setup() {
    createCanvas(cols * scl, rows * scl);
    background(0, 0, 0);
    stroke(255, 0, 0);
    noFill();
    rect(0, 0, cols * scl, rows * scl);
    frameRate(30);
    initializeSketch();
}

function initializeSketch() {

    snake = new Snake(scl, cols, rows);
    snake.setCoord(generateRandomPosition());

    food = new Food(scl);
    food.setCoord(generateRandomPosition());

    collision = new Collision(cols, rows);
}

function keyPressed() {
    snake.moveSnake(keyCode);
}


function generateRandomPosition() {
    var randomX = Math.floor(Math.random() * cols - 2);
    var randomY = Math.floor(Math.random() * rows - 2);

    randomX = randomX > 2 ? randomX : 2;
    randomY = randomY > 2 ? randomY : 2;

    randomX = randomX != cols ? randomX : cols - 2;
    randomY = randomY != rows ? randomY : rows - 2;

    return [randomX, randomY];
}

function draw() {

    background(0, 0, 0);
    stroke(255, 0, 0);
    noFill();
    rect(0, 0, cols * scl - 1, rows * scl - 1);

    if (collision.isObjectCollided(snake.getCoords(), food.getCoords())) {
        snake.grow();
        food.setCoord(generateRandomPosition());
    }
    food.foodLocation();
    snake.updateSnake();
    snake.showSnake();

    if (snake.endGame()) {
        background(255, 0, 0);
        textSize(32);
        fill(57, 255, 20);
        text('END GAME', (cols / 2 - 10) * scl, rows / 2 * scl);
        text('Press any key to restart', (cols / 2 - 18) * scl, (rows / 2 + 3) * scl);
        //noLoop();
        if (keyIsPressed === true) {
            initializeSketch();
        }
    }
}