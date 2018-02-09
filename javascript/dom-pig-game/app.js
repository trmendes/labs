/*
GAME RULES:

- The game has 2 players, playing in rounds - In each turn, a player rolls a
dice as many times as he whishes. Each result get added to his ROUND score -
BUT, if the player rolls a 1, all his ROUND score gets lost. After that, it's
the next player's turn - The player can choose to 'Hold', which means that his
ROUND score gets added to his GLBAL score. After that, it's the next player's
turn - The first player to reach 100 points on GLOBAL score wins the game

*/

/* TODO
 * SIX IN A ROLL - RESET SCORE
 * TWO DICES - IF ONE OF THEM IS ONE - LOOSE CURRENT SCORE
 * INPUT TYPE FOR MAX SCORE
 */

/* ---------------------------------------------------------------------------
 * PLAYERS
 * ---------------------------------------------------------------------------
 */

const maxScore = 100;

let scores, roundScore, player, sixInARollCnt;

function updateScore(player, value) {
    document.getElementById(`score-${player}`).textContent = value;
};

function updateCurrentScore(player, value) {
    document.getElementById(`current-${player}`).textContent = value;
};

function swapPlayer() {
    sixInARollCnt = 0;
    updateCurrentScore(player, roundScore);
    updateScore(player, scores[player]);

    document.getElementById('dice-box').style.display = 'none';
    if (scores[player] >= maxScore) {
        document.getElementById(`name-${player}`).textContent = "Winner";
        document.querySelector(`.player-${player}-panel`).classList.
            add('winner');
        document.querySelector(`.player-${player}-panel`).classList.
            remove('active');
    } else {
        document.querySelector(`.player-${player}-panel`).classList.
            remove('active');
        player = (player + 1) % 2;
        document.querySelector(`.player-${player}-panel`).classList.
            add('active');
    }
};

function init() {
    scores = [0, 0];
    roundScore = 0;
    player = 0;
    sixInARollCnt = 0;

    updateScore(0,0);
    updateScore(1,0);

    updateCurrentScore(0, 0);
    updateCurrentScore(1, 0);

    document.getElementById('dice-box').style.display = 'none';

    document.getElementById('name-0').textContent = 'Player 1';
    document.getElementById('name-1').textContent = 'Player 2';

    document.querySelector('.player-0-panel').classList.remove('winner');
    document.querySelector('.player-1-panel').classList.remove('winner');

    document.querySelector('.player-0-panel').classList.add('active');
    document.querySelector('.player-1-panel').classList.remove('active');
}

document.querySelector('.btn-new').addEventListener('click', () => {
    init();
});

document.querySelector('.btn-roll').addEventListener('click', () => {

    if (scores[player] >= maxScore) {
        return;
    }

    let diceA = Math.floor(Math.random() * 6) + 1;
    let diceB = Math.floor(Math.random() * 6) + 1;

    document.getElementById('dice-box').style.display = 'block';
    document.getElementById('dice1').src = `dice-${diceA}.png`;
    document.getElementById('dice2').src = `dice-${diceB}.png`;

    if ((diceA === 6) && (diceB === 6)) {
        ++sixInARollCnt;
    } else {
        sixInARollCnt = 0;
    }

    if (sixInARollCnt === 2) {
        roundScore = 0;
        scores[player] = 0;
        swapPlayer();
    } else {
        if ((diceA === 1) || (diceB === 1)) {
            roundScore = 0;
            swapPlayer();
        } else {
            roundScore += (diceA + diceB);
            updateCurrentScore(player, roundScore);
        }
    }
    document.getElementById('score-msg').textContent = `Player ${player} [Six in a rox: ${sixInARollCnt}/2] [last dices values [${diceA}:${diceB}]]`;
});

document.querySelector('.btn-hold').addEventListener('click', () => {
    if (scores[player] >= maxScore) {
        return;
    }

    scores[player]+= roundScore;
    roundScore = 0;
    swapPlayer();
});

init();
