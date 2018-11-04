class Food {
    constructor(scl) {
        this.scl = scl;
    }
    setCoord(coords){
        this.col = coords[0]; // x - column number
        this.row = coords[1]; // y - row number
        this.currentX = this.col * scl;
        this.currentY = this.row * scl;

    }

    foodLocation() {
        fill(255, 0, 0);
        noStroke();
        rect(this.currentX, this.currentY, scl, scl);
    }

    getCoords(){
        return [this.col,this.row];
    }
   
}