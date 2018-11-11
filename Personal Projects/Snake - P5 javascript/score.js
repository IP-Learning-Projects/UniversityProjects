class Score{
    
    constructor(){
        this.score = 0;
        this.highScore = typeof(localStorage['highScore']) == 'undefined' ? 0 : localStorage['highScore'];
    }

    getScore(){
        return this.score;
    }
    getHighScore(){
        return this.highScore;
    }
    incrementScore(){
        this.score++;
    }

    saveHighScore(){
        localStorage['highScore'] = this.score > this.highScore ? this.score : this.highScore;
    }

}