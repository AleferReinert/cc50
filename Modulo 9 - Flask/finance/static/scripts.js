/* Adiciona o zero na frente quando for menor que 10 */
function formatZero(data){
    if(data < 10){
        data = `0${data}`
    }
    return data;
}

let d = new Date(),
    day     = formatZero(d.getDate()),
    month   = formatZero(d.getMonth() + 1),
    year    = d.getFullYear(),
    hour    = formatZero(d.getHours()),
    minutes = formatZero(d.getMinutes()),
    seconds = formatZero(d.getSeconds()),
    timestamp = `${day}-${month}-${year} ${hour}:${minutes}:${seconds}`;

/* Coloca a data atual no input */
document.getElementById("timestamp").value = timestamp;