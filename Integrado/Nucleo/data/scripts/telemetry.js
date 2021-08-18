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

function setMotorPower(id, reading) {
    if (reading < 0) {
        document.getElementById(id + "-motor-power").style.color = "red";
        document.getElementById(id + "-motor-power").innerHTML = (reading * -1);
    } else {
        document.getElementById(id + "-motor-power").style.color = "green";
        document.getElementById(id + "-motor-power").innerHTML = reading;
    }
}

connection.onmessage = function(response) {
    let json = JSON.parse(response.data);

    if ("robot_name" in json) {
        document.getElementById("connection-status-text").innerHTML = "Connected to " + json["robot_name"];
    }

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

        if ("motor" in json["readings"]) {
            setMotorPower("left", json["readings"]["motor"][0]);
            setMotorPower("right", json["readings"]["motor"][1]);
        }
    }
}