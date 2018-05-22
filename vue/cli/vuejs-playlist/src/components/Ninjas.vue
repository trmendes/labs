<template>
  <div id="ninjas">
    <ul>
      <li v-for="ninja in ninjas" v-on:click="ninja.show = !ninja.show">
        <h2>{{ninja.name}}</h2>
        <h3 v-show="ninja.show">{{ ninja.speciality}}</h3>
      </li>
    </ul>
    <button v-on:click="deleteNinja">Delete Ninja</button>
  </div>
</template>

<script>
export default {
  props: {
    ninjas: {
      type: Array,
      required: true
    }
  },
  data() {
    return {
    }
  },
  methods: {
    deleteNinja: function() {
      this.ninjas.pop();
    }
  },
  // lifecycle hooks
  beforeCreate() {
    alert('before Create');
  },
  created() {
    /* Best place to fetch some data
      from a db or anywhere */
    alert('created');
  },
  beforeMount() {
    alert('befor Mount');
  },
  mounted() {
    /* The best place to manipulate a DOM */
    alert('monted');
  },
  beforeUpdate() {
    /* Any time we delete a Ninja VUE lifecycle
    will end up at this part and this leads to
    updated() to show the user a new screen */
    alert('before update');
  },
  updated() {
    /* A good place to manipulate a DOM
      cause it will be called after any updates to the screen like
    delete, edit, etc
      */
    alert('updated');
  }
}
</script>

<style>
#ninjas{
  width: 100%;
  max-width: 1200px;
  margin: 40px auto;
  padding: 0 20px;
  box-sizing: border-box;
}
ul {
  display: flex;
  flex-wrap: wrap;
  list-style-type: none;
  padding: 0;
}
li {
  flex-grow: 1;
  flex-basis: 300px;
  text-align: center;
  padding: 30px;
  border: 1px solid #222;
  margin: 10px;
}
</style>
