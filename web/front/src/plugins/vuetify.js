// Styles
import '@mdi/font/css/materialdesignicons.css'
import 'vuetify/styles'

// Vuetify
import { createVuetify } from 'vuetify'

export default createVuetify(
  {
    theme: {
      defaultTheme: 'sir',
      themes: {
        sir: {
          variables: {},
          colors: {
            primary: "#3498db",
            secondary: "#2ecc71",
            accent: "#e74c3c",
          }
        }
      }
    }
  }
)
