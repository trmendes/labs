const one = new Vue({
    el: '#vue-app-one',
    data: {
        title: 'Vue app one'
    },
    methods: {
    },
    computed: {
        greet: function() {
            return 'Hello from app one';
        }
    }
});

const two = new Vue({
    el: '#vue-app-two',
    data: {
        title: 'Vue app two'
    },
    methods: {
        changeTitle: function() {
            one.title = 'app one modified by app two';
        }
    },
    computed: {
        greet: function() {
            return 'This is app two \\o/';
        }
    }
});


