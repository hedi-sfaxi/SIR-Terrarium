import axios from "axios"

const middlewareBaseUrl = process.env.VUE_APP_MIDDLEWARE_BASE_URL

const instance = axios.create({
    baseURL: middlewareBaseUrl,
})

const getColumns = async () => {
    let result = { text: "utils.columns_ko", color: "error", columns: [] }
    try {
        const response = await instance.get("/columns")
        result = { text: "utils.columns_ok", color: "success", columns: response.data.columns }
    } catch (err) {
        console.log(err)
    }
    return result
}

const irrigate = async () => {
    let result = { text: "utils.irrigate_ko", color: "error" }
    try {
        await instance.get("/irrigate")
        result = { text: "utils.irrigate_ok", color: "success" }
    } catch (err) {
        console.log(err)
    }
    return result
}

const correlate = async (metric1, metric2) => {
    let result = { text: "utils.correlation_ko", color: "error" }
    try {
        await instance.get(`/correlation?param1=${metric1}&param2=${metric2}`)
        result = { text: "utils.correlation_ok", color: "success" }
    } catch (err) {
        console.log(err)
    }
    return result
}

const rupture = async () => {
    let result = { text: "utils.rupture_ko", color: "error" }
    try {
        await instance.get("/ruptures")
        result = { text: "utils.rupture_ok", color: "success" }
    } catch (err) {
        console.log(err)
    }
    return result
}

export default { getColumns, irrigate, correlate, rupture }
