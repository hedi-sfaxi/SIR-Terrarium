<template>
  <div class="d-flex justify-space-around">
    <v-menu>
      <template v-slot:activator="{ props }">
        <v-btn text v-bind="props">
            {{ current.text }}
            <v-icon>mdi-menu-down</v-icon>
            </v-btn>
      </template>
      <v-list>
        <v-list-item
          v-for="(item, index) in items"
          :key="index"
          :value="index"
           @click="changeLocale(item)"
        >
          <v-list-item-title>{{ item.text }}</v-list-item-title>
        </v-list-item>
      </v-list>
    </v-menu>
  </div>
</template>

<script>
export default {
    name: "LanguageSwitcher",

    data: () => ({
        current: { text: "", locale: "" },
        items: [
            { text: "Français", locale: "fr" },
            { text: "English", locale: "en" }
        ]
    }),

    methods: {
        changeLocale(item) {
            this.current = item;
            this.$i18n.locale = item.locale;
        }
    },

    mounted() {
        const locale = this.$i18n.locale;
        this.current = this.items.find(item => item.locale === locale);
    }
};
</script>