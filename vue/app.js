new Vue({
    el: "#vue-app",
    data: {
        name: 'Thiago'
    },
    methods: {
        greet: function () {
            return 'Good morning';
        },
        play: function (sport) {
            return `hey ${this.name}, let's play ${sport}`;
        }
    }
});
