<template>
    <nav>
        <v-app-bar app color="white">
            <v-app-bar-nav-icon @click="drawer = !drawer" class="text-black"></v-app-bar-nav-icon>
            <v-toolbar-title>
                <router-link to="/" class="text-secondary">{{ $t('nav.title') }}</router-link>
            </v-toolbar-title>
            <v-spacer></v-spacer>
            <LanguageSwitcher />
        </v-app-bar>
        <v-navigation-drawer v-model="drawer" app color="secondary">
            <v-list>
                <v-list-item v-for="item in items" :key="item.title" link @click="clickLinkInsideDiv($event)">
                    <v-list-item-title>
                        <v-icon class="text-white mr-2">{{ item.icon }}</v-icon>
                        <router-link :to="item.route" class="text-white">{{ $t(item.title) }}</router-link>
                    </v-list-item-title>
                </v-list-item>
            </v-list>
        </v-navigation-drawer>
    </nav>
</template>

<script>
import LanguageSwitcher from "@/components/LanguageSwitcher.vue";
export default {
    name: "NavBar",

    components: {
        LanguageSwitcher,
    },

    data: () => ({
        drawer: false,
        items: [
            { title: "nav.dashboard", icon: "mdi-view-dashboard", route: "/" },
            { title: "nav.control", icon: "mdi-gamepad-variant", route: "/control" },
            { title: "nav.settings", icon: "mdi-cog", route: "/settings" },
        ]
    }),

    methods: {
        clickLinkInsideDiv(event) {
            event.preventDefault();
            if (event) {
                const a = event.target.querySelector("a");
                if (a) {
                    a.click();
                }
            }
        },
    },
};
</script>

<style scoped>
a {
    text-decoration: none;
}
</style>