<template>
  <div>
    <keep-alive>
      <!--To do not destroy the data every time I change to a new component -->
      <compontent v-bind:is="component"></compontent>
    </keep-alive>
    <button v-on:click="showFormOne">Show form one</button>
    <button v-on:click="component = 'form-two'">Show form two</button>
  </div>
</template>

<script>

import formOne from './components/formOne.vue'
import formTwo from './components/formTwo.vue'

export default {
  components: {
    'form-one': formOne,
    'form-two': formTwo
  },
  data () {
    return {
      component: 'form-two'
    };
  },
  methods: {
    handleSubmit: function() {

    },
    showFormOne: function() {
      this.component = 'form-one';
    }
  }
}
</script>

<style scoped>
</style>
