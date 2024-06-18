<template>
    <div>
        <v-form @submit="submitForm">
            <v-container>
                <h1 class="display-1">Mail alert configuration</h1>
                <br>
                <v-row>
                    <v-col cols="12" sm="6">
                        <v-text-field v-model="email" label="Email" required></v-text-field>
                    </v-col>
                    <v-col cols="12" sm="6">
                        <v-text-field v-model="password" label="Password" type="password" required></v-text-field>
                    </v-col>
                </v-row>
                <v-row>
                    <v-col cols="12" sm="6">
                        <v-select v-model="smtpServer" label="SMTP Server" :items="smtpOptions" required @change="handleSmtpServerChange">
                        </v-select>
                    </v-col>
                    <v-col cols="12" sm="6" v-if="smtpServer === 'other'">
                        <v-text-field v-model="customSmtpServer" label="Custom SMTP Server" required></v-text-field>
                    </v-col>
                </v-row>
                <v-row>
                    <v-col>
                        <v-btn type="submit" color="primary" block>Submit</v-btn>
                    </v-col>
                </v-row>
            </v-container>

        </v-form>
    </div>
</template>

<script>
export default {
    data() {
        return {
            email: '',
            password: '',
            smtpServer: '',
            smtpOptions: ['outlook', 'gmail', 'other'],
        };
    },
    methods: {
        submitForm() {
            // Handle form submission logic here
            // You can access the form values using this.email, this.password, this.smtpServer
        }
    }
};
</script>