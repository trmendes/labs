<template>
  <div v-theme:column="'wide'" id="show-blogs">
    <h1>List Blog Titles</h1>
    <input type="text" v-model="search" placeholder="search blogs" />
    <div v-for="blog in filteredBlogs" class="single-blog">
      <h2 v-raibow>{{ blog.title | to-uppercase }}</h2>
      <article>{{blog.body | snippet }}</article>
    </div>
  </div>
</template>

<script>

import searchMixin from '../mixins/searchMixin';

export default {
  data() {
    return {
      blogs: [],
      search: ''
    }
  },
  created() {
    this.$http.get('http://jsonplaceholder.typicode.com/posts')
      .then(function(data) {
        this.blogs = data.body.slice(0, 10);
      });
  },
  /* Our LOCAL filters */
  filters: {
    toUppercase(value) {
      return value.toUpperCase();
    }
  },
  /* Our LOCAL directives */
  directives: {
    'raibow': {
      bind(el, binding, virtualNode) {
        el.style.color = "#" + Math.random().toString().slice(2,8);
      }
    }
  },
  mixins: [searchMixin]
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
