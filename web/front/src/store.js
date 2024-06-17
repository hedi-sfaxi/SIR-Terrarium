import { createStore } from 'vuex'

const store = createStore({
    state() {
        return {
            snackbar: {
                visible: false,
                color: "success",
                text: "",
            },
            analysis: {
                correlationRunning: false,
                ruptureRunning: false,
            }
        }
    },

    mutations: {
        setVisible(state, value) {
            state.snackbar.visible = value
        },

        setColor(state, value) {
            state.snackbar.color = value
        },

        setText(state, value) {
            state.snackbar.text = value
        },

        setCorrelationRunning(state, value) {
            state.analysis.correlationRunning = value
        },

        setRuptureRunning(state, value) {
            state.analysis.ruptureRunning = value
        },
    }
})

export default store