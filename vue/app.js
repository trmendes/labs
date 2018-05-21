new Vue({
    el: "#vue-app",
    data: {
        name: 'Thiago',
        website: 'https://tmendes.gitlab.io/38lbackpack/',
        websiteTag: '<a href="https://tmendes.gitlab.io/38lbackpack/">Another way to show my webpage</a>',
        age: 20,
        x: 0,
        y: 0
    },
    methods: {
        greet: function () {
            return 'Good morning';
        },
        play: function (sport) {
            return `hey ${this.name}, let's play ${sport}`;
        },
        addAge: function (amount) {
            this.age+=amount;
        },
        subAge: function (amount) {
            this.age-=amount;
        },
        updateXY: function(event) {
            this.x = event.x;
            this.y = event.y;
        },
        logName: function() {
            console.log('you entered your name');
        },
        logAge: function() {
            console.log('you entered your age');
        },
        logAltEnter: function() {
            console.log('you entered some text hitting alt enter after it');
        }
    }
});
