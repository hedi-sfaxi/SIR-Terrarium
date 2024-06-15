<template>
    <v-container class="mb-5 mt-2">
        <h2> {{ $t(title) }}</h2>
        <v-divider :thickness="6" class="border-opacity-100" color="success"></v-divider>
        <slot></slot>
    </v-container>
</template>

<script>
export default {
    name: 'SimpleSection',
    props: {
        title: {
            type: String,
            required: true
        }
    }
}
</script>