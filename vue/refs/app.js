new Vue({
    el: '#vue-app',
    data: {
        output: 'Your fav food',
        divOutput: ''
    },
    methods: {
        readRefs: function() {
            this.output = this.$refs.input.value;
            this.divOutput = this.$refs.test.innerText;
        }
    }
});
