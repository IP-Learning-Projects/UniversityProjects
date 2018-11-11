let snake;
let food;
let collision;
let score;
let scl = 20;
let height = window.innerHeight - (window.innerHeight/100);
let width = window.innerWidth - (window.innerWidth/100);
let cols = Math.floor(width / scl);
let rows = Math.floor(height / scl);
let isTappedToReset = false;
let isSwipeToReset = false;
let gameEnded = false;
let soundMovement;
let soundEat;
let soundDeath;

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
    gameEnded = false;
    soundMovement = new Audio('./assets/sounds/Movement.ogg');
    soundEat = new Audio('./assets/sounds/Eat.ogg');
    soundDeath = new Audio('./assets/sounds/Death.wav');

    snake = new Snake(scl, cols, rows);
    snake.setCoord(generateRandomPosition());

    food = new Food(scl);
    food.setCoord(generateRandomPosition());

    collision = new Collision(cols, rows);
    score = new Score();
}

function keyPressed() {
    snake.moveSnake(keyCode);
}

function swiped(event) {
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
    //console.log(event,isTappedToReset);
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
    if(gameEnded == false && (snake.getDir()[0] != 0 || snake.getDir()[1] != 0)){
        soundMovement.play();
    }
    background(0, 0, 0);
    stroke(255, 0, 0);
    noFill();
    rect(0, 0, cols * scl - 1, rows * scl - 1);

    if (collision.isObjectCollided(snake.getCoords(), food.getCoords())) {
        snake.grow();
        score.incrementScore();
        soundEat.play();
        food.setCoord(generateRandomPosition());
    }
    food.foodLocation();
    snake.updateSnake();
    snake.showSnake();

    if (snake.endGame()) {
        soundMovement.pause();
        soundEat.pause();
        if(gameEnded == false){
            soundDeath.play();
            gameEnded = true;
        }

        background(255, 0, 0);
        textSize(32);
        fill(57, 255, 20);
        text('Score: '+score.getScore(), (cols/ 2 - 6) * scl, (3) * scl);
        text('HighScore: '+score.getHighScore(), (cols/ 2 - 6) * scl, (6) * scl);
        text('GAME OVER', (cols/ 2 - 7) * scl, (rows / 2 - 0) * scl);
        text('Restart?', (cols / 2 - 5) * scl, (rows / 2 + 3) * scl);

        score.saveHighScore()
        //noLoop();
        if (keyIsPressed === true || isTappedToReset === true || isSwipeToReset === true) {
            isTappedToReset = false;
            isSwipeToReset = false;
            soundDeath.pause();
            initializeSketch();
        }
    }
}