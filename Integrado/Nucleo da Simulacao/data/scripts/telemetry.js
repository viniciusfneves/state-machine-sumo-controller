/*Abre a conexão com serviço WebSocket do ESP*/
var connection = new WebSocket("ws://" + location.hostname + ":81");

function setOpponentSensor(index, reading) {
    if (reading == true) {
        document.getElementById(index + "-op").style.background = "red";
    } else {
        document.getElementById(index + "-op").style.background = "black";
    }
}

connection.onmessage = function(response) {
    let json = JSON.parse(response.data);

    if ("readings" in json) {
        if ("opponent" in json["readings"]) {
            setOpponentSensor("far-left", json["readings"]["opponent"][0]);
            setOpponentSensor("left", json["readings"]["opponent"][1]);
            setOpponentSensor("center", json["readings"]["opponent"][2]);
            setOpponentSensor("right", json["readings"]["opponent"][3]);
            setOpponentSensor("far-right", json["readings"]["opponent"][4]);
        }
        if ("edge" in json["readings"]) {
            console.log(json["readings"]["edge"][0]);
            console.log(json["readings"]["edge"][1]);
        }
    }
}