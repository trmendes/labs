<template>
  <div id="add-blog">
    <h2>Add a New Blog Post</h2>
    <form>
      <label>Title:</label>
      <input type="text" v-model.lazy="blog.title" required />
      <label>Content:</label>
      <textarea v-model.lazy="blog.content"></textarea>
      <div id="checkboxes">
        <label>Ninjas</label>
        <input type="checkbox" value="ninjas" v-model="blog.categories" />
        <label>Wiards</label>
        <input type="checkbox" value="wizards" v-model="blog.categories" />
        <label>Gamers</label>
        <input type="checkbox" value="gamers" v-model="blog.categories" />
        <label>Climbers</label>
        <input type="checkbox" value="climbers" v-model="blog.categories" />
      </div>
      <div id="preview">
        <h3>Preview Blog</h3>
        <p>Blog title: {{ blog.title }}</p>
        <p>Blog content:</p>
        <p>{{ blog.content }}</p>
        <ul>
          <li v-for="categorie in blog.categories">{{ categorie }}</li>
        </ul>
      </div>
    </form>
  </div>
</template>

<script>
export default {
  data () {
    return {
      blog: {
        title: '',
        content: '',
        categories: []
      }
    }
  },
  methods: {
  }
}
</script>

<style>
#add-blog *{
  box-sizing: border-box;
}
#add-blog{
  margin: 20px auto;
  max-width: 500px;
}
label{
  display: block;
  margin: 20px 0 10px;
}
input[type="text"], textarea {
  display: block;
  width: 100%;
}

#preview {
  padding: 10px 20px;
  border: 1px dotted #ccc;
  margin: 30px 0;
}
h3{
  margin-top: 10px;
}
#checkboxes input{
  diplay: inline-block;
  margin-right: 10px;
}
#checkboxes label{
  diplay: inline-block;
}
</style>
