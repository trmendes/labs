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
    updateCurrentScore(player, roundScore);
    updateScore(player, scores[player]);

    document.querySelector('.dice').style.display = 'none';
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

    updateScore(0,0);
    updateScore(1,0);

    updateCurrentScore(0, 0);
    updateCurrentScore(1, 0);

    document.querySelector('.dice1').style.display = 'none';
    document.querySelector('.dice2').style.display = 'none';

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

    let dice1 = Math.floor(Math.random() * 6) + 1;
    let dice2 = Math.floor(Math.random() * 6) + 1;

    document.querySelector('.dice1').style.display = 'block';
    document.querySelector('.dice1').src = `dice-${dice}.png`;
    document.querySelector('.dice2').style.display = 'block';
    document.querySelector('.dice2').src = `dice-${dice}.png`;

    if ((dice1 === 1) || (dice2 === 1)) {
        roundScore = 0;
        swapPlayer();
    } else {
        roundScore += (dice1 + dice2);
        updateCurrentScore(player, roundScore);
    }
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
