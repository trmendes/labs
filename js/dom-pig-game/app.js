/*
GAME RULES:

- The game has 2 players, playing in rounds - In each turn, a player rolls a
dice as many times as he whishes. Each result get added to his ROUND score -
BUT, if the player rolls a 1, all his ROUND score gets lost. After that, it's
the next player's turn - The player can choose to 'Hold', which means that his
ROUND score gets added to his GLBAL score. After that, it's the next player's
turn - The first player to reach 100 points on GLOBAL score wins the game

*/

/* ---------------------------------------------------------------------------
 * PLAYERS
 * ---------------------------------------------------------------------------
 */

let scores = [0, 0];
let roundScore = 0;
let activePlayer = 0; /* 0 - 1th player, 1 - 2sd player */
let player = 0;

function updateScore(player, value) {
    document.getElementById(`score-${player}`).textContent = value;
};

function updateCurrentScore(player, value) {
    document.getElementById(`current-${player}`).textContent = value;
};

function swapPlayer() {
    updateCurrentScore(player, roundScore);
    updateScore(player, scores[player]);
    document.querySelector('.dice').style.display = 'none';
    document.querySelector(`.player-${player}-panel`).classList.remove('active');
    player = (player + 1) % 2;
    document.querySelector(`.player-${player}-panel`).classList.add('active');
};

updateScore(0,0);
updateScore(1,0);
updateCurrentScore(0, 0);
updateCurrentScore(1, 0);

document.querySelector('.btn-roll').addEventListener('click', () => {
    let dice = Math.floor(Math.random() * 6) + 1;

    document.querySelector('.dice').style.display = 'block';
    document.querySelector('.dice').src = `dice-${dice}.png`;

    if (dice == 1) {
        roundScore = 0;
        swapPlayer();
    } else {
        roundScore += dice;
        updateCurrentScore(player, roundScore);
    }
});

document.querySelector('.btn-hold').addEventListener('click', () => {
    scores[player]+= roundScore;
    roundScore = 0;
    swapPlayer();
});
