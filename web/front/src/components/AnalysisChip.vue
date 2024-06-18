<template>
    <div>
        <v-chip variant="elevated" class="mx-2" :color=color>
            {{ $t(statusText) }}
            <v-icon class="mx-1">
                {{ status }}
            </v-icon>
        </v-chip>
        <v-btn @click="updateStatus" icon color="primary">
            <v-icon size="small">
                mdi-refresh
            </v-icon>
        </v-btn>
    </div>
</template>

<script>
import utils from '../utils';
export default {

    data() {
        return {
            status: 'mdi-circle',
            color: 'gray',
            statusText: ''
        }
    },

    props: {
        taskId: String,
        forRupture: Boolean
    },

    async mounted() {
        await this.updateStatus();
    },

    watchers: {
        taskId: async function () {
            await this.updateStatus();
        }
    },

    methods: {
        async updateStatus() {
            let data = await utils.getTaskStatus(this.taskId);

            if (data.status === 'SUCCESS') {
                this.status = 'mdi-check-circle';
                this.color = 'success';
                this.statusText = 'controlView.analysis.status.success';

                if (this.forRupture) {
                    this.$store.commit('setRuptureRunning', false);
                } else {
                    this.$store.commit('setCorrelationRunning', false);
                }

            } else if (data.status === 'IN_PROGRESS') {
                this.status = 'mdi-progress-alert';
                this.color = 'warning';
                this.statusText = 'controlView.analysis.status.inProgress';
            } else {
                this.status = 'mdi-alert';
                this.color = 'error';
                this.statusText = 'controlView.analysis.status.error';

                if (this.forRupture) {
                    this.$store.commit('setRuptureRunning', false);
                } else {
                    this.$store.commit('setCorrelationRunning', false);
                }
            }
        }
    }
}
</script>
