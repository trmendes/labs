import Vue from 'vue'
import App from './App.vue'
import VueResource from 'vue-resource'

Vue.use(VueResource);

/* Custom directive */
Vue.directive('raibow', {
  bind(el, binding, virtualNode) {
    el.style.color = "#" + Math.random().toString().slice(2,8);
  }
});

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

/* Our filters */

Vue.filter('filter-to-uppercase', function(value) {
  return value.toUpperCase();
});

Vue.filter('snippet', function(value) {
  return value.slice(0,100) + '...';
});

new Vue({
  el: '#app',
  render: h => h(App)
})
