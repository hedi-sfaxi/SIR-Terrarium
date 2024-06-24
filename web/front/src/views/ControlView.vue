<template>
    <v-container class="d-flex flex-column">
        <Snackbar />
        <SimpleSection title="controlView.directActions.title">
            <div class="mt-5">
                <p class="mb-5">{{ $t("controlView.directActions.intro") }}</p>
                <div class="d-flex justify-space-around">
                    <v-btn color="primary" @click="irrigate()">
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

                <div class="text-center my-5">
                    <img :src="imageSrc" alt="Terrarium Live Image">
                    <p>{{ $t("controlView.camMessage") }}</p>
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
                    <AnalysisChip v-if="correlationTaskId" :taskId="correlationTaskId" :forRupture="false" />
                    <v-btn color="primary" @click="correlate()">
                        {{ $t("controlView.analysis.correlation") }}
                    </v-btn>
                </div>
                <div class="d-flex justify-space-around">
                    <p>{{ $t("controlView.analysis.ruptureText") }}</p>
                    <AnalysisChip v-if="ruptureTaskId" :taskId="ruptureTaskId" :forRupture="true" />
                    <v-btn color="primary" @click="rupture">
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
import AnalysisChip from '../components/AnalysisChip.vue';
import utils from '../utils';
export default {
    data() {
        return {
            imageSrc: process.env.VUE_APP_CAM_STREAM_URL,
            selectedMetrics: [],
            items: [],
            correlationTaskId: '',
            ruptureTaskId: ''
        };
    },
    components: {
        SimpleSection,
        Snackbar,
        AnalysisChip
    },
    async mounted() {
        this.items = await this.getColumns();
    },
    methods: {
        handleButtonClick(action) {
            // Handle button click event here
            console.log('Button clicked:', action);
        },

        async getColumns() {
            this.$store.commit('setVisible', true);
            let message = await utils.getColumns();
            this.$store.commit('setColor', message.color);
            this.$store.commit('setText', message.text);
            return message.columns;
        },

        async correlate() {
            if (this.$store.state.analysis.correlationRunning || this.selectedMetrics.length !== 2) {
                this.$store.commit('setVisible', true);
                this.$store.commit('setColor', 'warning');
                this.$store.commit('setText', 'controlView.analysis.correlationRunning');
            } else {
                this.correlationTaskId = '';
                this.$store.commit("setCorrelationRunning", true);
                this.$store.commit('setVisible', true);
                let message = await utils.correlate(this.selectedMetrics[0], this.selectedMetrics[1]);
                this.$store.commit('setColor', message.color);
                this.$store.commit('setText', message.text);
                this.correlationTaskId = message.taskId;
            }
        },

        async rupture() {
            if (this.$store.state.analysis.ruptureRunning) {
                this.$store.commit('setVisible', true);
                this.$store.commit('setColor', 'warning');
                this.$store.commit('setText', 'controlView.analysis.ruptureRunning');
            } else {
                this.ruptureTaskId = '';
                this.$store.commit("setRuptureRunning", true);
                this.$store.commit('setVisible', true);
                let message = await utils.rupture();
                this.$store.commit('setColor', message.color);
                this.$store.commit('setText', message.text);
                this.ruptureTaskId = message.taskId;
            }
        },

        async irrigate() {
            this.$store.commit('setVisible', true);
            let message = await utils.irrigate();
            this.$store.commit('setColor', message.color);
            this.$store.commit('setText', message.text);
        }
    }
};
</script>

<style scoped></style>