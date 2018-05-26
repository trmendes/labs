import Vue from 'vue'
import App from './App.vue'
import VueResource from 'vue-resource'

Vue.use(VueResource);

/* Custom GLOBAL directive */

Vue.directive('theme', {
  bind(el, binding, virtualNode) {
    if (binding.value === "wide") {
      el.style.maxWidth = "1200px";
    } else if (binding === "narrow") {
      el.style.maxWidth = "320px";
    }

    if (binding.arg === "column") {
      el.style.background = "#ddd";
      el.style.padding = "20px";
    }
  }
});

/* Our GLOBAL filters */

Vue.filter('snippet', function(value) {
  return value.slice(0,100) + '...';
});

new Vue({
  el: '#app',
  render: h => h(App)
})
