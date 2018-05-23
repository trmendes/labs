<template>
  <div>
    <h1>Please fill out our form</h1>
    <form>
      <div id="form-header">
        <h3>Form One - Contact Us</h3>
        <p>Fill in this form to contact us</p>
      </div>
      <div id="form-fields">
        <input type="text" placeholder="name" required />
        <label>Your Message:</label>
        <textarea></textarea>
      </div>
      <div id="form-controls">
        <button v-on:click="handleSubmit">Send</button>
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
