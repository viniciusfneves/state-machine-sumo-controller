import { connection, requestEvent } from "./websocket_handler.js";
import * as Colors from "./colors.js";

window.onload = function () {
	document.getElementById("event-start").addEventListener("click", (_) => requestEvent("start"));
	document.getElementById("event-arm").addEventListener("click", (_) => requestEvent("arm"));
	document.getElementById("event-disengage").addEventListener("click", (_) => requestEvent("disengage"));
};

function setOpponentSensor(id, reading) {
	document.getElementById(id + "Op").style.display = "block";
	if (reading == true) {
		document.getElementById(id + "Op").style.background = Colors.bright_red;
	} else {
		document.getElementById(id + "Op").style.background = Colors.std_black;
	}
}

function setEdgeSensor(id, reading) {
	document.getElementById(id + "Edge").style.display = "block";
	if (reading == true) {
		document.getElementById(id + "Edge").style.background = Colors.std_ambar;
	} else {
		document.getElementById(id + "Edge").style.background = Colors.std_black;
	}
}

function setMotorPower(id, reading) {
	if (reading < 0) {
		document.getElementById(id + "MotorPower").style.color = Colors.light_red;
		document.getElementById(id + "MotorPower").innerHTML = reading * -1;
	} else {
		document.getElementById(id + "MotorPower").style.color = Colors.std_green;
		document.getElementById(id + "MotorPower").innerHTML = reading;
	}
}

function clearRobotState() {
	document.getElementById("initial-strategy-status-circle").style.background = Colors.std_color;
	document.getElementById("search-strategy-status-circle").style.background = Colors.std_color;
	document.getElementById("chase-strategy-status-circle").style.background = Colors.std_color;
}

var OPSensors = ["leftSide", "farLeft", "left", "center", "right", "farRight", "rightSide"];

function refreshOpSensorReadings(opReadings) {
	OPSensors.forEach((sensor) => {
		if (sensor in opReadings) {
			setOpponentSensor(sensor, opReadings[sensor]);
		} else {
			document.getElementById(sensor + "Op").style.display = "none";
		}
	});
}

var EDGESensors = ["frontLeft", "frontRight", "rearLeft", "rearRight"];

function refreshEdgeSensorReadings(edgeReadings) {
	EDGESensors.forEach((sensor) => {
		if (sensor in edgeReadings) {
			setEdgeSensor(sensor, edgeReadings[sensor]);
		} else {
			document.getElementById(sensor + "Edge").style.display = "none";
		}
	});
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
	}
	if ("readings" in json) {
		var readings = json["readings"];

		updateRobotState(readings["robot_status"]);

		if ("opponent" in readings) refreshOpSensorReadings(readings["opponent"]);

		if ("edge" in readings) refreshEdgeSensorReadings(readings["edge"]);

		setMotorPower("left", readings["motor"][0]);
		setMotorPower("right", readings["motor"][1]);
	}
};
