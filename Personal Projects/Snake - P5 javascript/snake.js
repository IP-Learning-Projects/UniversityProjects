class Snake {

    constructor(scl, maxCols, maxRows) {
        this.scl = scl;
        this.xSpeed = 0;
        this.ySpeed = 0;
        this.body = [];
        this.maxCols = maxCols;
        this.maxRows = maxRows;

    }
    setCoord(coords) {
        this.col = coords[0]; // x - column number
        this.row = coords[1]; // y - row number

    }

    setDir(x, y) {
        this.xSpeed = x;
        this.ySpeed = y;
    }
    getDir() {
        return [this.xSpeed, this.ySpeed];
    }

    getCoords() {
        return [this.col, this.row];
    }

    moveSnake(keyCode) {
        if (keyCode === LEFT_ARROW && this.lastDirection !== "right") {
            this.setDir(-1, 0);
            this.lastDirection = "left";
        } else if (keyCode === RIGHT_ARROW && this.lastDirection !== "left") {
            this.setDir(1, 0);
            this.lastDirection = "right";
        } else if (keyCode === DOWN_ARROW && this.lastDirection !== "up") {
            this.setDir(0, 1);
            this.lastDirection = "down";
        } else if (keyCode === UP_ARROW && this.lastDirection !== "down") {
            this.setDir(0, -1);
            this.lastDirection = "up";
        }
    }

    moveSnakeSwipe(event) {
        console.log(event);
        if (event.type == "swiped-left" && this.lastDirection != "right") {
            //left
            this.setDir(-1, 0);
            this.lastDirection = "left";
        }else if (event.type == "swiped-right" && this.lastDirection != "left") {
            //right
            this.setDir(1, 0);
            this.lastDirection = "right";
        }else if (event.type == "swiped-down" && this.lastDirection != "up") {
            //down
            this.setDir(0, 1);
            this.lastDirection = "down";
        }else if (event.type == "swiped-up" && this.lastDirection != "down") {
            //up
            this.setDir(0, -1);
            this.lastDirection = "up";
        }
    }

    moveSnakeTap(event) {
        if(this.xSpeed == 0 && this.ySpeed == 0){
            this.setDir(1, 0);
            this.lastDirection = "right";
        }else if (this.lastDirection == "up") {
            //left
            this.setDir(-1, 0);
            this.lastDirection = "left";
        }else if (this.lastDirection == "down") {
            //right
            this.setDir(1, 0);
            this.lastDirection = "right";
        }else if (this.lastDirection == "left") {
            //down
            this.setDir(0, 1);
            this.lastDirection = "down";
        }else if (this.lastDirection == "right") {
            //up
            this.setDir(0, -1);
            this.lastDirection = "up";
        }
    }


    showSnake() {
        fill(57, 255, 20);
        stroke(0);
        for (var i = 0; i < this.body.length; i++) {
            rect(this.body[i][0] * this.scl, this.body[i][1] * this.scl, scl, scl);
        }
    }

    grow() {
        var currentPosition = [this.col, this.row]
        this.body.push(currentPosition);
    }

    updateSnake() {
        collision = new Collision(this.maxCols, this.maxRows);
        this.col = this.col + this.xSpeed;
        this.row = this.row + this.ySpeed;
        var currentPosition = [this.col, this.row]
        this.body.shift();
        this.body.push(currentPosition);

    }

    endGame() {
        collision = new Collision(this.maxCols, this.maxRows);
        if (collision.isWallCollided([this.col, this.row])) {
            this.setDir(0, 0);
            return true;
        }
        for (var i = this.body.length - 2; i >= 0; i--) {
            if (collision.isObjectCollided([this.col, this.row], this.body[i])) {
                this.setDir(0, 0);
                return true
            }
        }
        return false;
    }


}