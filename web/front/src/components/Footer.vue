<template>
    <v-footer class="bg-indigo-lighten-1 text-center d-flex flex-column mt-5">
        <div>
            <a v-for="el in links" :key="el.icon" class="mx-4 text-black" :href="el.link" target="_blank" plain>
                <v-icon class="mdi mdi-github-face">
                    {{ el.icon }}
                </v-icon>
            </a>
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
            { icon: 'mdi-github', link: "https://github.com/hedi-sfaxi/SIR-Terrarium" }
        ],
    }),
}
</script>