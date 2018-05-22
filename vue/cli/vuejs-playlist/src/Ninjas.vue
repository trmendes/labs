<template>
  <div>
    <h1>List of Ninjas</h1>
    <ul>
      <li v-for="ninja in ninjas">{{ ninja }}</li>
    </ul>
  </div>
</template>

<script>
export default {
  data() {
    return {
      ninjas: ['Shimano', 'Japa', 'Black']
    }
  }
}
</script>

<style scoped>
h1 {
  color: green;
}
</style>
