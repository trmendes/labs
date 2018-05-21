new Vue({
    el: "#vue-app",
    data: {
        name: 'Thiago',
        website: 'https://tmendes.gitlab.io/38lbackpack/',
        websiteTag: '<a href="https://tmendes.gitlab.io/38lbackpack/">Another way to show my webpage</a>'
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
