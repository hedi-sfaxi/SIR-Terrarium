const middlewareBaseUrl = process.env.VUE_APP_MIDDLEWARE_BASE_URL

const getColumns = () => {
    let result = { text: "utils.columns_ko", color: "error", columns: [] }
    fetch(`${middlewareBaseUrl}/columns`)
        .then(data => {
            result = { text: "utils.columns_ok", color: "success", columns: data }
        })
        .catch(err => {
            console.log(err)
        })
    return result
}

const irrigate = () => {
    let result = { text: "utils.irrigate_ko", color: "error" }
    fetch(`${middlewareBaseUrl}/irrigate`)
        .then(() => {
            result = { text: "utils.irrigate_ok", color: "success" }
        })
        .catch(err => {
            console.log(err)
        })
    return result
}

const correlate = (metric1, metric2) => {
    let result = { text: "utils.correlation_ko", color: "error" }
    fetch(`${middlewareBaseUrl}/correlation?param1=${metric1}&param2=${metric2}`)
        .then(() => {
            result = { text: "utils.correlation_ok", color: "success" }
        })
        .catch(err => {
            console.log(err)
        })
    return result
}

const rupture = () => {
    let result = { text: "utils.rupture_ko", color: "error" }
    fetch(`${middlewareBaseUrl}/ruptures`)
        .then(() => {
            result = { text: "utils.rupture_ok", color: "success" }
        })
        .catch(err => {
            console.log(err)
        })
    return result
}

export default { getColumns, irrigate, correlate, rupture }