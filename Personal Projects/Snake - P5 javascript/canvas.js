let snake;
let food;
let collision;
let scl = 20;
let height = window.innerHeight - (window.innerHeight/100);
let width = window.innerWidth - (window.innerWidth/100);
let cols = Math.floor(width / scl);
let rows = Math.floor(height / scl);
let isTappedToReset = false;
let isSwipeToReset = false;


document.addEventListener('click',tapped,false);
document.addEventListener('swiped-left',swiped);
document.addEventListener('swiped-right',swiped);
document.addEventListener('swiped-up',swiped);
document.addEventListener('swiped-down',swiped);

function setup() {
    createCanvas(cols * scl, rows * scl);
    background(0, 0, 0);
    stroke(255, 0, 0);
    noFill();
    rect(0, 0, cols * scl, rows * scl);
    frameRate(8);
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

function swiped(event) {
    // DIRECTION_NONE	    1
    // DIRECTION_LEFT	    2
    // DIRECTION_RIGHT	    4
    // DIRECTION_UP	        8
    // DIRECTION_DOWN	    16
    // DIRECTION_HORIZONTAL	6
    // DIRECTION_VERTICAL	24
    // DIRECTION_ALL	    30
    snake.moveSnakeSwipe(event);
    if(snake.endGame()){
        isSwipeToReset = true;
    }else{
        isSwipeToReset = false;
    }
}

function tapped(event) {
    snake.moveSnakeTap(event);
    if(snake.endGame()){
        isTappedToReset = true;
    }else{
        isTappedToReset = false;
    }
    console.log(event,isTappedToReset);
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
        text('END GAME', (cols/ 2 - 4) * scl, rows / 2 * scl);
        text('Press any key to restart', (cols / 2 - 8) * scl, (rows / 2 + 3) * scl);
        //noLoop();
        if (keyIsPressed === true || isTappedToReset === true || isSwipeToReset === true) {
            isTappedToReset = false;
            isSwipeToReset = false;
            initializeSketch();
        }
    }
}