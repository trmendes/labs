interface Stark {
    name : String;
    job? : String; /* Optional \o/*/
}

function prinName(stark : Stark) {
    console.log(stark.name);
}

prinName({name: 'Ed'});
prinName({age: 36}); /* FUCK I LOVE IT */
