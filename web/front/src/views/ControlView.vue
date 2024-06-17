<template>
    <v-container class="d-flex flex-column">
        <Snackbar />
        <SimpleSection title="controlView.directActions.title">
            <div class="mt-5">
                <p class="mb-5">{{ $t("controlView.directActions.intro") }}</p>
                <div class="d-flex justify-space-around">
                    <v-btn color="primary" @click="handleButtonClick('water')">
                        <v-icon>
                            mdi-water
                        </v-icon>
                        {{ $t("controlView.directActions.irrigate") }}
                    </v-btn>
                    <v-btn color="primary" @click="handleButtonClick('light')">
                        <v-icon>
                            mdi-lightbulb-on
                        </v-icon>
                        {{ $t("controlView.directActions.light") }}
                    </v-btn>
                </div>

                <div class="center my-5">
                    <img :src="imageSrc" alt="Terrarium Live Image" style="width: 500px;">
                </div>
            </div>
        </SimpleSection>
        <SimpleSection title="controlView.analysis.title">
            <div class="mt-5">
                <p class="mb-5">{{ $t("controlView.analysis.intro") }}</p>
                <div class="d-flex justify-space-around">
                    <div style="width: 300px;">
                        <v-combobox clearable chips multiple label="metrics" v-model="selectedMetrics" :items="items"
                            variant="outlined"></v-combobox>
                    </div>
                    <v-btn color="primary" @click="correlate()">
                        {{ $t("controlView.analysis.correlation") }}
                    </v-btn>
                </div>
                <div class="d-flex justify-space-around">
                    <p>{{ $t("controlView.analysis.ruptureText") }}</p>
                    <v-btn color="primary">
                        {{ $t("controlView.analysis.rupture") }}
                    </v-btn>
                </div>
            </div>
        </SimpleSection>
    </v-container>
</template>

<script>
import SimpleSection from '../components/SimpleSection.vue';
import Snackbar from '../components/SnackBar.vue';
import utils from '../utils';
export default {
    data() {
        return {
            imageSrc: "https://img-3.journaldesfemmes.fr/55Pa2VVqjc0hXSevl8ddLxHV53Y=/1500x/smart/6f75f95c0d54470fa206aa78fe6ed3a8/ccmcms-jdf/39925288.jpg", // Replace with your image URL
            selectedMetrics: [],
            items: this.getColumns()
        };
    },
    components: {
        SimpleSection,
        Snackbar
    },
    methods: {
        handleButtonClick(action) {
            // Handle button click event here
            console.log('Button clicked:', action);
        },

        getColumns() {
            this.$store.commit('setVisible', true);
            let message = utils.getColumns();
            this.$store.commit('setColor', message.color);
            this.$store.commit('setText', message.text);
            return message.columns;
        },

        correlate() {
            this.$store.commit('setVisible', true);
            let message = utils.correlate(this.selectedMetrics[0], this.selectedMetrics[1]);
            this.$store.commit('setColor', message.color);
            this.$store.commit('setText', message.text);
        },

        rupture() {
            this.$store.commit('setVisible', true);
            let message = utils.rupture();
            this.$store.commit('setColor', message.color);
            this.$store.commit('setText', message.text);
        }
    }
};
</script>

<style scoped>
.grid-container {
    display: grid;
    justify-content: center;
}

.center {
    text-align: center;
}

/* Add your custom styles here */
</style>