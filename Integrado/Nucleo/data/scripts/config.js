import { connection, requestEvent, sendRequest, setParameters } from './websocket_handler.js'
import * as Colors from './colors.js'

window.onload = function () {
	document.getElementById("event_start").addEventListener("click", _ => requestEvent("start"));
	document.getElementById("event_disengage").addEventListener("click", _ => requestEvent("disengage"));
	document.getElementById("event_arm").addEventListener("click", _ => requestEvent("arm"));
	document.getElementById("set-button").addEventListener("click", _ => setParameters());
	document.getElementById("debug-icon").addEventListener("click", _ => toggleDebbugingOptions());
	document.getElementById("debug-send-button").addEventListener("click", _ => sendCustomMessage());
	setInterval(function () {
        // Verifica se o campo de start-time é válido e adapta conforme regulado com o robô ou precisando de atualização
		if (document.getElementById("start-time-value").value < 0) {
            alert("O campo Start Time não aceita valores negativos. Corrijá-o para valores válidos");
            document.getElementById("start-time-value").value = 0;
		} else {
            // Verifica se há alterações não salvas no campo Start Time
			if (document.getElementById("start-time-value").value == start_time) {
				document.getElementById("start-time-value").style.background = Colors.std_green;
			} else {
				document.getElementById("start-time-value").style.background = Colors.std_ambar;
			}
		}
        
        // Verifica se há alterações não salvas no campo P do PID
        if (document.getElementById("P-regulator-value").value == pid_kp) {
            document.getElementById("P-regulator-value").style.background = Colors.std_green;
        } else {
            document.getElementById("P-regulator-value").style.background = Colors.std_ambar;
        }

        // Verifica se há alterações não salvas no campo I do PID
        if (document.getElementById("I-regulator-value").value == pid_ki) {
            document.getElementById("I-regulator-value").style.background = Colors.std_green;
        } else {
            document.getElementById("I-regulator-value").style.background = Colors.std_ambar;
        }

        // Verifica se há alterações não salvas no campo D do PID
        if (document.getElementById("D-regulator-value").value == pid_kd) {
            document.getElementById("D-regulator-value").style.background = Colors.std_green;
        } else {
            document.getElementById("D-regulator-value").style.background = Colors.std_ambar;
        }

		// Verifica se há alterações não salvas no campo arcAgularSpeed do arco
		if (document.getElementById("arcAgularSpeed-regulator-value").value == arco_arcAgularSpeed) {
            document.getElementById("arcAgularSpeed-regulator-value").style.background = Colors.std_green;
        } else {
            document.getElementById("arcAgularSpeed-regulator-value").style.background = Colors.std_ambar;
        }

		// Verifica se há alterações não salvas no campo angle do arco
		if (document.getElementById("angle-regulator-value").value == arco_angle) {
            document.getElementById("angle-regulator-value").style.background = Colors.std_green;
        } else {
            document.getElementById("angle-regulator-value").style.background = Colors.std_ambar;
        }

		// Verifica se há alterações não salvas no campo arcTimeout do arco
		if (document.getElementById("arcTimeout-regulator-value").value == arco_arcTimeout) {
            document.getElementById("arcTimeout-regulator-value").style.background = Colors.std_green;
        } else {
            document.getElementById("arcTimeout-regulator-value").style.background = Colors.std_ambar;
        }
	}, 200);
};

// Variáveis que guardam infos de configurações para verificação posterior no código
var modes;
var initial_strategys;
var search_strategys;
var chase_strategys;
var ctrl_types;
var ctrl_maps;
var ctrl_filters;
var settingUp = true;
var lastCtrlstatus = "disconnected";
var start_time;
var pid_kp;
var pid_ki;
var pid_kd;
var arco_arcAgularSpeed;
var arco_angle;
var arco_arcTimeout;
var buttonNameExceptions = {
							"rc": "RC",
							"bt ps4":"PS4",
							"game standard": "Game STD",
							"rc standard": "RC STD",
							"rc inverted": "RC INV"
						};

// Atualiza as informações na tela sobre as configurações do robô de start_time e constantes do PID
function updateParameters(start_time, pid_kp, pid_ki, pid_kd, arco_arcAgularSpeed, arco_angle, arco_arcTimeout) {
	document.getElementById("start-time-value").value = start_time;
	document.getElementById("P-regulator-value").value = pid_kp;
	document.getElementById("I-regulator-value").value = pid_ki;
	document.getElementById("D-regulator-value").value = pid_kd;
	document.getElementById("arcAgularSpeed-regulator-value").value = arco_arcAgularSpeed;
	document.getElementById("angle-regulator-value").value = arco_angle;
	document.getElementById("arcTimeout-regulator-value").value = arco_arcTimeout;
}

function clearRobotState(){
	document.getElementById("armed-status-circle").style.background = Colors.std_color;
	document.getElementById("starting-status-circle").style.background = Colors.std_color;
	document.getElementById("fight-status-circle").style.background = Colors.std_color;
	document.getElementById("disabled-status-circle").style.background = Colors.std_color;
}

// Quando recebe dados do robô
connection.onmessage = function (response) {
	let json = JSON.parse(response.data);

	// Processa o nome do robô recebido
	if ("info" in json) {
		document.getElementById("connection-status-text").innerHTML = "Conectado à " + json["info"]["robot_name"];
		let titulo = document.getElementsByTagName("title");
		if(titulo.length > 0){
			titulo.item(0).innerHTML = json["info"]["robot_name"] + " Controller";
		}
		if(settingUp){
			modes = json["info"]["available_modes"];
			makeConfigButtons(modes, 'mode');
			initial_strategys = json["info"]["available_initial_strategies"];
			makeConfigButtons(initial_strategys, 'initial');
			search_strategys = json["info"]["available_search_strategies"];
			makeConfigButtons(search_strategys, 'search');
			chase_strategys = json["info"]["available_chase_strategies"];
			makeConfigButtons(chase_strategys, 'chase');
			ctrl_types = json["info"]["available_ctrl_types"];
			makeConfigButtons(ctrl_types, 'ctrl_type');
			ctrl_maps = json["info"]["available_ctrl_maps"];
			makeConfigButtons(ctrl_maps, 'ctrl_map');
			ctrl_filters = json["info"]["available_ctrl_filters"];
			makeConfigButtons(ctrl_filters, 'ctrl_filter');
			settingUp = false;
		}
	}

	// Processa Array de configurações do robô
	if ("configurations" in json) {
		// Altera a variável global start_time, pid_kp... etc
		start_time = json["configurations"]["start_time"];
		pid_kp = json["configurations"]["pid"]["kp"];
		pid_ki = json["configurations"]["pid"]["ki"];
		pid_kd = json["configurations"]["pid"]["kd"];
		arco_arcAgularSpeed = json["configurations"]["arc_angular_speed"];
		arco_angle["configurations"]["arc_rot_initial_angle"];
		arco_arcTimeout["configurations"]["arc_timeout"];
		updateParameters(start_time, pid_kp, pid_ki, pid_kd, arco_arcAgularSpeed, arco_angle, arco_arcTimeout);

		let mode = json["configurations"]["mode"];
		let initial = json["configurations"]["initial_move"];
		let search = json["configurations"]["search"];
		let chase = json["configurations"]["chase"];
		let type = json["configurations"]["controller"]["commander"];
		let map = json["configurations"]["controller"]["mapping"];
		let filter = json["configurations"]["controller"]["filter"];
		updateConfigButtons(mode, initial, search, chase, type, map, filter);

		if(mode == "auto"){
			document.getElementById("auto-settings").style.display = "block";
			document.getElementById("rc-settings").style.display = "none";
		}
		if(mode == "rc"){
			document.getElementById("auto-settings").style.display = "none";
			document.getElementById("rc-settings").style.display = "block";
		}
	}

	// Atualiza Status do Robô
	if("readings" in json){
		clearRobotState();
		let status = json["readings"]["robot_status"];
		if (status == "ready") {
			document.getElementById("armed-status-circle").style.background = Colors.std_ambar;
		}

		if (status == "starting") {
			document.getElementById("starting-status-circle").style.background = Colors.std_blue;
		}

		if (status == "stopped") {
			document.getElementById("disabled-status-circle").style.background = Colors.std_red;
		}

		if (status == "exec_initial") {
			document.getElementById("fight-status-circle").style.background = Colors.std_green;
		}

		if (status == "exec_search") {
			document.getElementById("fight-status-circle").style.background = Colors.std_green;		
		}

		if (status == "exec_chase") {
			document.getElementById("fight-status-circle").style.background = Colors.std_green;		
		}

		if (status == "exec_controller") {
			document.getElementById("fight-status-circle").style.background = Colors.std_green;		
		}
	}

	if("controller" in json){
		let actualCtrlStatus = json["controller"]["connection_status"]
		if(actualCtrlStatus != lastCtrlstatus){
			lastCtrlstatus = actualCtrlStatus;
			if(actualCtrlStatus == "connected"){
				document.getElementById("ctrl-status-img").src = "../../assets/ps4_full.png";
			}else{
				document.getElementById("ctrl-status-img").src = "../../assets/ps4_all_bk.png";
			}
		}
		if("charging_status" in json["controller"]){
			let ctrl_charging = json["controller"]["charging_status"];
			if(ctrl_charging == "true"){
				document.getElementById("ctrl-battery").innerHTML = "Charging...";
			} else {
				let battery = json["controller"]["battery"];
				document.getElementById("ctrl-battery").innerHTML = battery + "0%";
			}
		}
	}
};

function makeConfigButtons(availableConfigs, configType){
	availableConfigs.forEach(element => {
		let widget = document.createElement("button");
		widget.addEventListener("click", _ => sendRequest(configType, element));
		widget.id = configType+'_'+element;
		let elementName = element.replace('_', ' ');
		if (Object.keys(buttonNameExceptions).includes(elementName)){
			elementName = buttonNameExceptions[elementName];
		} else {
			elementName = elementName.replace(/\w\S*/g, (w) => (w.replace(/^\w/, (c) => c.toUpperCase())));
		}
		widget.innerHTML = elementName;
		document.getElementById(configType+"-container").appendChild(widget);
	});
}

function updateConfigButtons(mode, initial, search, chase, type, map, filter){
	clearConfigButtons();
	document.getElementById('mode_'+mode).style.background = Colors.highlight_color;
	document.getElementById('initial_'+initial).style.background = Colors.highlight_color;
	document.getElementById('search_'+search).style.background = Colors.highlight_color;
	document.getElementById('chase_'+chase).style.background = Colors.highlight_color;
	document.getElementById('ctrl_type_'+type).style.background = Colors.highlight_color;
	document.getElementById('ctrl_map_'+map).style.background = Colors.highlight_color;
	document.getElementById('ctrl_filter_'+filter).style.background = Colors.highlight_color;
}

function clearConfigButtons(){
	document.getElementById('mode_auto').style.background = Colors.std_color;
	document.getElementById('mode_rc').style.background = Colors.std_color;
	initial_strategys.forEach(element => {
		document.getElementById('initial_'+element).style.background = Colors.std_color;
	});
	search_strategys.forEach(element => {
		document.getElementById('search_'+element).style.background = Colors.std_color;
	});
	chase_strategys.forEach(element => {
		document.getElementById('chase_'+element).style.background = Colors.std_color;
	});
	ctrl_types.forEach(element => {
		document.getElementById('ctrl_type_'+element).style.background = Colors.std_color;
	});
	ctrl_maps.forEach(element => {
		document.getElementById('ctrl_map_'+element).style.background = Colors.std_color;
	});
	ctrl_filters.forEach(element => {
		document.getElementById('ctrl_filter_'+element).style.background = Colors.std_color;
	});
}

function toggleDebbugingOptions() {
	let debug_container = document.getElementById("debugging-container");
	if (debug_container.style.display == "inline-block") {
		document.getElementById("debug-icon").src = 
		"../../assets/debug_icon_bw.png";
		debug_container.style.display = "none";
	}else {
		document.getElementById("debug-icon").src = 
		"../../assets/debug_icon_color.png";
		debug_container.style.display = "inline-block";
	}
}

function sendCustomMessage(){
	let message = document.getElementById("debug-message-text-field").value;
	document.getElementById("debug-message-text-field").value = "";
	connection.send(message);
}
