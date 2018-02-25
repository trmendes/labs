'use strict';

const rand = () => {
    const keys = [65, 83, 68, 70, 71, 72, 74, 75, 76];
    const randKey = Math.floor(Math.random() * 10 % keys.length);
    const audioAuto = document.querySelector(
        `audio[data-key="${keys[randKey]}"]`);
    if (audioAuto) {
        audioAuto.currentTime = 0;
        audioAuto.play();
    }
}

const removeTransition = function (e) {
    if (e.propertyName !== 'transform') {
        return;
    }
    this.classList.remove('playing');
};

window.addEventListener('keydown', event => {
    const audio = document.querySelector(`audio[data-key="${event.keyCode}"]`);
    const key = document.querySelector(`div[data-key="${event.keyCode}"]`);

    if (!audio) {
        return;
    }
    audio.currentTime = 0;
    audio.play();
    key.classList.add('playing');
});


const keys = document.querySelectorAll('.key');
keys.forEach(key => key.addEventListener('transitionend',  removeTransition));
