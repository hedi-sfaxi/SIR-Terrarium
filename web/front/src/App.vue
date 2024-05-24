<template>
  <v-app>
    <NavBar />
    <v-main class="h-100">
      <router-view />
    </v-main>
    <Footer></Footer>
  </v-app>
</template>


<script>
import NavBar from './components/NavBar.vue';
import Footer from './components/Footer.vue';

export default {
  name: "App",
  data: () => ({
    //
  }),
  components: { NavBar, Footer }
};
</script>
