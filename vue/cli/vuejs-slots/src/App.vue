<template>
  <div>
    <form-helper>
      <div slot="slot-form-header">
        <h3>This is the title of the form</h3>
        <p>information about the form</p>
      </div>
      <div slot="slot-form-fields">
        <input type="text" placeholder="name" required>
        <input type="password" placeholder="password" required>
      </div>
      <div slot="slot-form-controls">
        <button v-on:click="handleSubmit">Submit</button>
      </div>
    </form-helper>
  </div>
</template>

<script>

import formHelper from './components/formHelper.vue'

export default {
  components: {
    'form-helper': formHelper
  },
  data () {
    return {
      title: 'ScopedTitle'
    };
  },
  methods: {
    handleSubmit: function() {

    }
  }
}
</script>

<style scoped>
</style>
