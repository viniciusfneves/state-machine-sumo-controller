/*Abre a conexão com serviço WebSocket do ESP*/
var connection = new WebSocket("ws://" + location.hostname + ":81");

// Conexão estabelecida
connection.onopen = function () {
	document.getElementById("connection-status-circle").style.background = "#00770c";
	document.getElementById("connection-status-circle").style.color = "#00770c";
	document.getElementById("connection-status-text").innerHTML = "Connected";
};

// Erro na conexão
connection.onerror = function() {
    document.getElementById("connection-status-circle").style.background = "#bd0101";
    document.getElementById("connection-status-text").style.color = "#bd0101";
    document.getElementById("connection-status-text").innerHTML = "Erro de conexão";
}

// Conexão encerrada
connection.onclose = function(event) {
    document.getElementById("connection-status-circle").style.background = "#bd0101";
    document.getElementById("connection-status-text").style.color = "#bd0101";
    document.getElementById("connection-status-text").innerHTML = "O robô encerrou a conxão";
}

function requestEvent(event) {
	connection.send('{ "event_request" : "' + event + '" }');
}

function setOpponentSensor(id, reading) {
	document.getElementById(id + "-op").style.display = "block";
	if (reading == true) {
		document.getElementById(id + "-op").style.background = "red";
	} else {
		document.getElementById(id + "-op").style.background = "black";
	}
}

function setEdgeSensor(id, reading) {
	document.getElementById(id + "-edge").style.display = "block";
	if (reading == true) {
		document.getElementById(id + "-edge").style.background = "yellow";
	} else {
		document.getElementById(id + "-edge").style.background = "black";
	}
}

function setMotorPower(id, reading) {
	if (reading < 0) {
		document.getElementById(id + "-motor-power").style.color = "red";
		document.getElementById(id + "-motor-power").innerHTML = reading * -1;
	} else {
		document.getElementById(id + "-motor-power").style.color = "green";
		document.getElementById(id + "-motor-power").innerHTML = reading;
	}
}

var NUMBER_OF_OPPONENT_SENSORS = 0;

function refreshOpSensorReadings(opReadings) {
	switch (NUMBER_OF_OPPONENT_SENSORS) {
		case 2:
			setOpponentSensor("left", opReadings[0]);
			setOpponentSensor("right", opReadings[1]);
			break;
		case 3:
			setOpponentSensor("left", opReadings[0]);
			setOpponentSensor("center", opReadings[1]);
			setOpponentSensor("right", opReadings[2]);
			break;
		case 5:
			setOpponentSensor("far-left", opReadings[0]);
			setOpponentSensor("left", opReadings[1]);
			setOpponentSensor("center", opReadings[2]);
			setOpponentSensor("right", opReadings[3]);
			setOpponentSensor("far-right", opReadings[4]);
			break;
		case 7:
			setOpponentSensor("left-side", opReadings[0]);
			setOpponentSensor("far-left", opReadings[1]);
			setOpponentSensor("left", opReadings[2]);
			setOpponentSensor("center", opReadings[3]);
			setOpponentSensor("right", opReadings[4]);
			setOpponentSensor("far-right", opReadings[5]);
			setOpponentSensor("right-side", opReadings[6]);
			break;
	}
}

var NUMBER_OF_EDGE_SENSORS = 0;

function refreshEdgeSensorReadings(edgeReadings) {
	switch (NUMBER_OF_EDGE_SENSORS) {
		case 2:
			setEdgeSensor("front-left", edgeReadings[0]);
			setEdgeSensor("front-right", edgeReadings[1]);
			break;
		case 4:
			setEdgeSensor("front-left", edgeReadings[0]);
			setEdgeSensor("front-right", edgeReadings[1]);
			setEdgeSensor("rear-left", edgeReadings[2]);
			setEdgeSensor("rear-right", edgeReadings[4]);
			break;
	}
}

connection.onmessage = function (response) {
	let json = JSON.parse(response.data);

	if ("robot_name" in json) {
		document.getElementById("connection-status-text").innerHTML =
			"Connected to " + json["robot_name"];
	}

	if ("available_opponent_sensors" in json) {
		NUMBER_OF_OPPONENT_SENSORS = json["available_opponent_sensors"];
	}

	if ("available_edge_sensors" in json) {
		NUMBER_OF_EDGE_SENSORS = json["available_edge_sensors"];
	}

	if ("readings" in json) {
		if ("opponent" in json["readings"]) {
			refreshOpSensorReadings(json["readings"]["opponent"]);
		}

		if ("edge" in json["readings"]) {
			refreshEdgeSensorReadings(json["readings"]["edge"]);
		}

		if ("motor" in json["readings"]) {
			setMotorPower("left", json["readings"]["motor"][0]);
			setMotorPower("right", json["readings"]["motor"][1]);
		}
	}
};
