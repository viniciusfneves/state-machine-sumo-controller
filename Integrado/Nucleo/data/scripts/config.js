/*Abre a conexão com serviço WebSocket do ESP*/
var connection = new WebSocket("ws://" + location.hostname + ":81");

// Estilos e cores padrão usadas
var std_color = '#868686'; // Define a cor do botão das estratégias disponíveis
var highlight_color = '#008080'; // Define a cor do botão das estratégias selecionadas
var std_red = '#bd0101';
var std_green = '#00770c';
var std_ambar = '#cc8b00';

window.onload = function () {
	setInterval(function () {
        // Verifica se o campo de start-time é válido e adapta conforme regulado com o robô ou precisando de atualização
		if (document.getElementById("start-time-value").value < 0) {
            alert("O campo Start Time não aceita valores negativos. Corrijá-o para valores válidos");
            document.getElementById("start-time-value").value = 0;
		} else {
            // Verifica se há alterações não salvas no campo Start Time
			if (document.getElementById("start-time-value").value == start_time) {
				document.getElementById("start-time-value").style.background = std_green;
			} else {
				document.getElementById("start-time-value").style.background = std_ambar;
			}
		}
        
        // Verifica se há alterações não salvas no campo P do PID
        if (document.getElementById("P-regulator-value").value == pid_kp) {
            document.getElementById("P-regulator-value").style.background = std_green;
        } else {
            document.getElementById("P-regulator-value").style.background = std_ambar;
        }

        // Verifica se há alterações não salvas no campo I do PID
        if (document.getElementById("I-regulator-value").value == pid_ki) {
            document.getElementById("I-regulator-value").style.background = std_green;
        } else {
            document.getElementById("I-regulator-value").style.background = std_ambar;
        }

        // Verifica se há alterações não salvas no campo D do PID
        if (document.getElementById("D-regulator-value").value == pid_kd) {
            document.getElementById("D-regulator-value").style.background = std_green;
        } else {
            document.getElementById("D-regulator-value").style.background = std_ambar;
        }
	}, 200);
};

// Conexão estabelecida
connection.onopen = function () {
	document.getElementById("connection-status-circle").style.background = std_green;
	document.getElementById("connection-status-text").style.color = std_green;
	document.getElementById("connection-status-text").innerHTML = "Connected";
};

// Erro na conexão
connection.onerror = function () {
	document.getElementById("connection-status-circle").style.background = std_red;
	document.getElementById("connection-status-text").style.color = std_red;
	document.getElementById("connection-status-text").innerHTML = "Erro de conexão";
};

// Conexão encerrada
connection.onclose = function (event) {
	document.getElementById("connection-status-circle").style.background = std_red;
	document.getElementById("connection-status-text").style.color = std_red;
	document.getElementById("connection-status-text").innerHTML = "Conexão encerrada";
};

// Variáveis que guardam infos de configurações para verificação posterior no código
var initial_strategys;
var search_strategys;
var chase_strategys;
var settingUp = true;
var start_time;
var pid_kp;
var pid_ki;
var pid_kd;

// Envia um request pro robô para alterar sua configuração de estratégias ou emitir um evento para a máquina
function sendRequest(requestType, request) {
	connection.send('{"' + requestType + '":"' + request + '"}');
}

// Envia um request pro robô para alterar sua configuração de parâmetros de start_time e constantes do PID
// Pega os valores automaticamente dos campos da página de configurações
function setParameters(){
    let parameter_start_time = document.getElementById("start-time-value").value;
    let parameter_pid_kp = document.getElementById("P-regulator-value").value;
    let parameter_pid_ki = document.getElementById("I-regulator-value").value;
    let parameter_pid_kd = document.getElementById("D-regulator-value").value;
    connection.send('{"start_time":' + parameter_start_time + ',"pid":{"kp":' + parameter_pid_kp + ',"ki":' + parameter_pid_ki + ',"kd":' + parameter_pid_kd + '}}');
}

// Atualiza as informações na tela sobre as configurações do robô de start_time e constantes do PID
function updateVariableSettings(start_time, pid_kp, pid_ki, pid_kd) {
	document.getElementById("start-time-value").value = start_time;
	document.getElementById("P-regulator-value").value = pid_kp;
	document.getElementById("I-regulator-value").value = pid_ki;
	document.getElementById("D-regulator-value").value = pid_kd;
}

function clearRobotState(){
	document.getElementById("armed-status-circle").style.background = std_color;
	document.getElementById("fight-status-circle").style.background = std_color;
	document.getElementById("disabled-status-circle").style.background = std_color;
}

// Quando recebe dados do robô
connection.onmessage = function (response) {
	let json = JSON.parse(response.data);

	// Processa o nome do robô recebido
	if ("info" in json) {
		document.getElementById("connection-status-text").innerHTML = "Connected to " + json["info"]["robot_name"];
		if(settingUp){
			initial_strategys = json["info"]["available_initial_strategies"];
			makeStrategyButtons(initial_strategys, 'initial');
			search_strategys = json["info"]["available_search_strategies"];
			makeStrategyButtons(search_strategys, 'search');
			chase_strategys = json["info"]["available_chase_strategies"];
			makeStrategyButtons(chase_strategys, 'chase');
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
		updateVariableSettings(start_time, pid_kp, pid_ki, pid_kd);

		let mode = json["configurations"]["mode"];
		let initial = json["configurations"]["initial_move"];
		let search = json["configurations"]["search"];
		let chase = json["configurations"]["chase"];
		updateStrategyButtons(mode, initial, search, chase);
		
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
		let status = json["readings"]["robot_status"];
		if (status == "ready") {
			clearRobotState();
			document.getElementById("armed-status-circle").style.background = std_ambar;
		}

		if (status == "starting") {
			clearRobotState();
			document.getElementById("fight-status-circle").style.background = std_green;
		}

		if (status == "stopped") {
			clearRobotState();
			document.getElementById("disabled-status-circle").style.background = std_red;
		}

		if (status == "exec_initial") {
			clearRobotState();
			document.getElementById("fight-status-circle").style.background = std_green;		}

		if (status == "exec_search") {
			clearRobotState();
			document.getElementById("fight-status-circle").style.background = std_green;		}

		if (status == "exec_chase") {
			clearRobotState();
			document.getElementById("fight-status-circle").style.background = std_green;		}
	}
};

function makeStrategyButtons(strategyList, strategyType){
	strategyList.forEach(element => {
		let widget = document.createElement("button");
		widget.addEventListener("click", _ => sendRequest(strategyType, element));
		widget.id = strategyType+'_'+element;
		let elementName = element.replace('_', ' ');
		elementName = elementName.replace(/\w\S*/g, (w) => (w.replace(/^\w/, (c) => c.toUpperCase())));;
		widget.innerHTML = elementName;
		document.getElementById(strategyType+"-container").appendChild(widget);
	});
}

function updateStrategyButtons(mode, initial, search, chase){
	clearStrategyButtons();
	document.getElementById('mode_'+mode).style.background = highlight_color;
	document.getElementById('initial_'+initial).style.background = highlight_color;
	document.getElementById('search_'+search).style.background = highlight_color;
	document.getElementById('chase_'+chase).style.background = highlight_color;
}

function clearStrategyButtons(){
	document.getElementById('mode_auto').style.background = std_color;
	document.getElementById('mode_rc').style.background = std_color;
	initial_strategys.forEach(element => {
		document.getElementById('initial_'+element).style.background = std_color;
	});
	search_strategys.forEach(element => {
		document.getElementById('search_'+element).style.background = std_color;
	});
	chase_strategys.forEach(element => {
		document.getElementById('chase_'+element).style.background = std_color;
	});
}