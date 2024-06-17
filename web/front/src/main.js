import { createApp } from 'vue'
import App from './App.vue'
import vuetify from './plugins/vuetify'
import { loadFonts } from './plugins/webfontloader'
import i18n from './plugins/i18n'
import router from './router'
import store from './store'

loadFonts()

createApp(App)
  .use(router)
  .use(i18n)
  .use(vuetify)
  .use(store)
  .mount('#app')
