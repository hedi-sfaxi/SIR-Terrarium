import { createApp } from 'vue'
import App from './App.vue'
import vuetify from './plugins/vuetify'
import { loadFonts } from './plugins/webfontloader'
import i18n from './plugins/i18n'
import router from './router'

loadFonts()

createApp(App).use(router).use(i18n)
  .use(vuetify)
  .mount('#app')
