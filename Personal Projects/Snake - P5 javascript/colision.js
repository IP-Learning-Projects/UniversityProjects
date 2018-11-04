class Collision {
    constructor(maxCol,maxRow){
        this.maxCol = maxCol;
        this.maxRow = maxRow;
    }

    isObjectCollided(coords1,coords2){
        var col1 = coords1[0];
        var row1 = coords1[1];
        var col2 = coords2[0];
        var row2 = coords2[1];
        if(col1 == col2 && row1 == row2){
            return true;
        }
        return false;
    }

    isWallCollided(coords){
        var col = coords[0];
        var row = coords[1];
        if(col < 0 || col >= this.maxCol){
            return true;
        }
        if(row < 0 || row >= this.maxRow){
            return true;
        }
        return false;
    }
}