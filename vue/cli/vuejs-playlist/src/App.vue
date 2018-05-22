<template>
  <div id="app">
    <h1>{{ title }} </h1>
    <p> {{ greeting() }} </p>
  </div>
</template>

<script>
export default {
  name: 'app',
  data () {
    return {
      title: 'Your first Vue file, woooo!'
    }
  },
  methods: {
    greeting: function() {
      return 'hi there';
    }
  }
}
</script>

<style>

</style>
