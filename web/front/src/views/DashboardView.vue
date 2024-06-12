<template>
    <div style="height: 100%;">
        <iframe
            :src="grafanaBaseUrl + '/d/edmdv2hpqy5tse/sensor?orgId=1&from=1718198978023&to=1718220578023&theme=light'"
            width="100%" height="100%">
        </iframe>
    </div>
</template>

<script>
export default {
    name: 'DashboardView',
    data: () => ({
        grafanaBaseUrl: 'http://grafana:3000' // "http://192.168.69.85:3000" // for debug
    }),
}
</script>
