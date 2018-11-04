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
    
    getCoords() {
        return [this.col, this.row];
    }

    moveSnake(keyCode) {
        if (keyCode === LEFT_ARROW && this.lastKeyCode !== RIGHT_ARROW) {
            this.setDir(-1, 0);
            this.lastKeyCode = keyCode;
        } else if (keyCode === RIGHT_ARROW && this.lastKeyCode !== LEFT_ARROW) {
            this.setDir(1, 0);
            this.lastKeyCode = keyCode;
        } else if (keyCode === DOWN_ARROW && this.lastKeyCode !== UP_ARROW) {
            this.setDir(0, 1);
            this.lastKeyCode = keyCode;
        } else if (keyCode === UP_ARROW && this.lastKeyCode !== DOWN_ARROW) {
            this.setDir(0, -1);
            this.lastKeyCode = keyCode;
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
            return true;
        }
        for (var i = this.body.length - 2; i >= 0; i--) {
            if (collision.isObjectCollided([this.col, this.row], this.body[i])) {
                return true
            }
        }
        return false;
    }


}