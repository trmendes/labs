<template>
  <footer>
    <p>{{ title }} - {{ copyright }}</p>
  </footer>
</template>

<script>

import { bus } from '../main';

export default {
  props: {
    title: {
      type: String,
      required: true
    }
  },
  data() {
    return {
      copyright: 'Creative Commons'
    }
  },
  created() {
    bus.$on('titleChanged', (data) => {
      this.title = data;
    });
  }
}
</script>

<style scoped>
footer {
  background: #222;
  padding: 6px;
}

p {
  color: lightgreen;
  text-align: center;
}

</style>
