import { connection, requestEvent } from './websocket_handler.js'
import * as Colors from './colors.js'

window.onload = function (){
	document.getElementById("event_start").addEventListener("click", _ => requestEvent("start"));
	document.getElementById("event_disengage").addEventListener("click", _ => requestEvent("disengage"));
}

function setOpponentSensor(id, reading) {
	document.getElementById(id + "-op").style.display = "block";
	if (reading == true) {
		document.getElementById(id + "-op").style.background = Colors.bright_red;
	} else {
		document.getElementById(id + "-op").style.background = Colors.std_black;
	}
}

function setEdgeSensor(id, reading) {
	document.getElementById(id + "-edge").style.display = "block";
	if (reading == true) {
		document.getElementById(id + "-edge").style.background = Colors.std_ambar;
	} else {
		document.getElementById(id + "-edge").style.background = Colors.std_black;
	}
}

function setMotorPower(id, reading) {
	if (reading < 0) {
		document.getElementById(id + "-motor-power").style.color = Colors.light_red;
		document.getElementById(id + "-motor-power").innerHTML = reading * -1;
	} else {
		document.getElementById(id + "-motor-power").style.color = Colors.std_green;
		document.getElementById(id + "-motor-power").innerHTML = reading;
	}
}

function clearRobotState(){
	document.getElementById("initial-strategy-status-circle").style.background = Colors.std_color;
	document.getElementById("search-strategy-status-circle").style.background = Colors.std_color;
	document.getElementById("chase-strategy-status-circle").style.background = Colors.std_color;
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

function updateRobotState(robot_status) {
	if (robot_status == "ready") {
		clearRobotState();
	}

	if (robot_status == "starting") {
		clearRobotState();
	}

	if (robot_status == "stopped") {
		clearRobotState();
	}

	if (robot_status == "exec_initial") {
		clearRobotState();
		document.getElementById("initial-strategy-status-circle").style.background = Colors.std_green;
	}

	if (robot_status == "exec_search") {
		clearRobotState();
		document.getElementById("search-strategy-status-circle").style.background = Colors.std_green;
	}

	if (robot_status == "exec_chase") {
		clearRobotState();
		document.getElementById("chase-strategy-status-circle").style.background = Colors.std_green;
	}
}

connection.onmessage = function (response) {
	let json = JSON.parse(response.data);

	if ("info" in json) {
		document.getElementById("connection-status-text").innerHTML = "Connected to " + json["info"]["robot_name"];
		NUMBER_OF_OPPONENT_SENSORS = json["info"]["available_opponent_sensors"];
		NUMBER_OF_EDGE_SENSORS = json["info"]["available_edge_sensors"];
	}
	if ("readings" in json) {
		updateRobotState(json["readings"]["robot_status"]);
		refreshOpSensorReadings(json["readings"]["opponent"]);
		refreshEdgeSensorReadings(json["readings"]["edge"]);
		setMotorPower("left", json["readings"]["motor"][0]);
		setMotorPower("right", json["readings"]["motor"][1]);
	}
};
