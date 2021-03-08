/*Abre a conexão com serviço WebSocket do ESP*/
var connection = new WebSocket("ws://" + location.hostname + ":81");

// Conexão estabelecida
connection.onopen = function() {
    document.getElementById("connection-status-circle").style.background = "#00770c";
    document.getElementById("connection-status-circle").style.color = "#00770c";
    document.getElementById("connection-status-text").innerHTML = "Connected";
}

// Erro na conexão
connection.onerror = function() {
    document.getElementById("connection-status-circle").style.background = "#bd0101";
    document.getElementById("connection-status-text").style.color = "#bd0101";
    document.getElementById("connection-status-text").innerHTML = "ERRO!";
}

// Conexão encerrada
connection.onclose = function(event) {
    if (event.wasClean) {
        document.getElementById("connection-status-circle").style.background = "#e4c200";
        document.getElementById("connection-status-text").innerHTML = "O robô encerrou a conxão";
    }
}

function requestEvent(event) {
    connection.send('{ "event_request" : "' + event + '" }');
    console.log('{ "event_request" : "' + event + '" }');
}

function setOpponentSensor(id, reading) {
    if (reading == true) {
        document.getElementById(id + "-op").style.background = "red";
    } else {
        document.getElementById(id + "-op").style.background = "black";
    }
}

function setEdgeSensor(id, reading) {
    if (reading == true) {
        document.getElementById(id + "-edge").style.background = "yellow";
    } else {
        document.getElementById(id + "-edge").style.background = "black";
    }
}

connection.onmessage = function(response) {
    let json = JSON.parse(response.data);
    console.log(response.data);

    if ("readings" in json) {
        if ("opponent" in json["readings"]) {
            setOpponentSensor("far-left", json["readings"]["opponent"][0]);
            setOpponentSensor("left", json["readings"]["opponent"][1]);
            setOpponentSensor("center", json["readings"]["opponent"][2]);
            setOpponentSensor("right", json["readings"]["opponent"][3]);
            setOpponentSensor("far-right", json["readings"]["opponent"][4]);
        }

        if ("edge" in json["readings"]) {
            setEdgeSensor("left", json["readings"]["edge"][0]);
            setEdgeSensor("right", json["readings"]["edge"][1]);
        }

        if ("motor" in json["readings"]) {}
    }
}