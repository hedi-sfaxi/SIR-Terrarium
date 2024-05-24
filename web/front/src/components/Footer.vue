<template>
    <v-footer class="bg-indigo-lighten-1 text-center d-flex flex-column mt-5">
        <div>
            <v-btn v-for="el in links" :key="el.icon" class="mx-4 black--text" :href="el.link" target="_blank"
                plain>
                <v-icon>
                    {{ el.icon }}
                </v-icon>
            </v-btn>
        </div>

        <div class="pt-0">
            Texte du footer
        </div>

        <v-divider></v-divider>

        <div>
            <v-icon>mdi-copyright</v-icon> {{ new Date().getFullYear() }} — <strong>{{ $t('nav.title') }}</strong>
        </div>
    </v-footer>
</template>

<script>
export default {
    name: 'FooterBar',
    data: () => ({
        links: [
            { icon: 'mdi-github', link: "" }
        ],
    }),
}
</script>