<template>
  <div>
    <h1>Please fill out our form</h1>
    <form>
      <div id="form-header">
        <h3>Form Two - Log in</h3>
        <p>Enter your details to log-in</p>
      </div>
      <div id="form-fields">
        <input type="text" placeholder="username" required />
        <input type="password" placeholder="password" required />
      </div>
      <div id="form-controls">
        <button v-on:click="handleSubmit">Login</button>
      </div>
    </form>
  </div>
</template>

<script>

export default {
  componets: {

  },
  data() {
    return {

    };
  },
  methods: {
    handleSubmit: function() {

    }
  }
}
</script>

<style scoped>
h1 {
  color: red;
}
</stule>
