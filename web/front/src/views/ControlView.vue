<template>
    <div class="grid-container">
        <div class="center" style="margin: 30px;">
            <v-btn v-for="action in actions" :key="action" @click="handleButtonClick(action.value)"
                style="margin-right: 10px;">
                <v-icon left>{{ action.icon }}</v-icon>
                {{ $t(action.value) }}
            </v-btn>
        </div>
        <div class="center" style="margin: 10px;">
            <!-- Renders an image element with a live image of the terrarium (updated every half hour?) -->
            <img :src="imageSrc" alt="Terrarium Live Image" style="width: 500px;">
        </div>
    </div>
</template>

<script>
export default {
    data() {
        return {
            imageSrc: "https://img-3.journaldesfemmes.fr/55Pa2VVqjc0hXSevl8ddLxHV53Y=/1500x/smart/6f75f95c0d54470fa206aa78fe6ed3a8/ccmcms-jdf/39925288.jpg", // Replace with your image URL
            actions: [
                { icon: 'mdi-water', value: 'controlView.irrigate' },
                { icon: 'mdi-lightbulb', value: 'controlView.light' }
            ]
        };
    },
    methods: {
        handleButtonClick(action) {
            // Handle button click event here
            console.log('Button clicked:', action);
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