import { createStore } from 'vuex'

const store = createStore({
    state() {
        return {
            snackbar: {
                visible: false,
                color: "success",
                text: "",
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
        }
    },
})

export default store