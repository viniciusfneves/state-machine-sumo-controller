import * as Colors from './colors.js'

/*Abre a conexão com serviço WebSocket do ESP*/
export var connection = new WebSocket("ws://" + location.hostname + ":81");

// Conexão estabelecida
connection.onopen = function () {
	document.getElementById("connection-status-circle").style.background = Colors.std_green;
	document.getElementById("connection-status-text").style.color = Colors.std_green;
	document.getElementById("connection-status-text").innerHTML = "Connected";
};

// Erro na conexão
connection.onerror = function () {
	document.getElementById("connection-status-circle").style.background = Colors.std_red;
	document.getElementById("connection-status-text").style.color = Colors.std_red;
	document.getElementById("connection-status-text").innerHTML = "Erro de conexão";
};

// Conexão encerrada
connection.onclose = function (event) {
	document.getElementById("connection-status-circle").style.background = Colors.std_red;
	document.getElementById("connection-status-text").style.color = Colors.std_red;
	document.getElementById("connection-status-text").innerHTML = "Conexão encerrada";
};

// Envia um request para o robô emitir um evento para a máquina
export function requestEvent(event) {
	connection.send('{ "event_request" : "' + event + '" }');
}

// Envia um request pro robô para alterar sua configuração de estratégias
export function sendRequest(requestType, request) {
	connection.send('{"' + requestType + '":"' + request + '"}');
}

// Envia um request pro robô para alterar sua configuração de parâmetros de start_time e constantes do PID
// Pega os valores automaticamente dos campos da página de configurações
export function setParameters() {
    let parameter_start_time = document.getElementById("start-time-value").value;
    let parameter_pid_kp = document.getElementById("P-regulator-value").value;
    let parameter_pid_ki = document.getElementById("I-regulator-value").value;
    let parameter_pid_kd = document.getElementById("D-regulator-value").value;
    connection.send('{"start_time":' + parameter_start_time + ',"pid":{"kp":' + parameter_pid_kp + ',"ki":' + parameter_pid_ki + ',"kd":' + parameter_pid_kd + '}}');
}