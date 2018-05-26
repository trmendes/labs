<template>
  <div v-theme:column="'wide'" id="show-blogs">
    <h1>All Blog Articles</h1>
    <input type="text" v-model="search" placeholder="search blogs" />
    <div v-for="blog in filteredBlogs" class="single-blog">
      <h2 v-raibow>{{ blog.title | filter-to-uppercase }}</h2>
      <article>{{blog.body | snippet }}</article>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      blogs: [],
      search: ''
    }
  },
  computed: {
    filteredBlogs: function() {
      return this.blogs.filter(blog => blog.title.match(this.search));
    }
  },
  created() {
    this.$http.get('http://jsonplaceholder.typicode.com/posts')
      .then(function(data) {
        this.blogs = data.body.slice(0, 10);
      });
  }
}
</script>

<style>
#show-blogs {
  max-width: 800px;
  margin: 0 auto;
}
.single-blog {
  padding: 20px;
  margin: 20px;
  box-sizing: border-box;
  background: #eee;
}
</style>
