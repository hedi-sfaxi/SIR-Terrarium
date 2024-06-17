<template>
    <div class="text-center">
        <v-snackbar v-model="snackbar.visible" :timeout="timeout" :color="snackbar.color">
            <div v-if="!snackbar.text" class="text-center">
                <v-progress-circular indeterminate color="white"></v-progress-circular>
            </div>
            <p v-else>
                {{ $t(snackbar.text) }}
            </p>

            <template v-slot:actions>
                <v-btn color="white" variant="text" @click="close()">
                    Close
                </v-btn>
            </template>
        </v-snackbar>
    </div>
</template>

<script>
export default {
    data: () => ({
        timeout: 10000
    }),

    computed: {
        snackbar() {
            return this.$store.state.snackbar
        },
    },

    methods: {
        close() {
            this.$store.commit('setVisible', false);
            this.$store.commit('setText', '');
        }
    }
}
</script>