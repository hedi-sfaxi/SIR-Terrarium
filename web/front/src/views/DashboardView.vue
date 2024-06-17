<template>
    <div style="height: 100%;">
        <iframe :src="grafanaBaseUrl + '/d/edmdv2hpqy5tse/sensor?orgId=1&from=now-5m&to=now&theme=light'" width="100%"
            height="100%">
        </iframe>
    </div>
</template>

<script>
export default {
    name: 'DashboardView',
    data: () => ({
        grafanaBaseUrl: process.env.VUE_APP_GRAFANA_BASE_URL
    }),
}
</script>
