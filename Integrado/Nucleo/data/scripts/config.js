/*Abre a conexão com serviço WebSocket do ESP*/
var connection = new WebSocket("ws://" + location.hostname + ":81");

// Enum com os tipos de estratégias aceitas pelo robô
const strategy_type = {
    mode: "mode",
    initial: "initial",
    search: "search",
    chase: "chase"
}

// Enum com os modos de operação
const mode_selector = {
    auto: "auto",
    rc: "rc"
}

// Enum com estratégias iniciais
const initial_move_strategy = {
    none: "none",
    full_frente: "full_frente",
    zig_zag: "zig_zag"
}

// Enum com estratégias de busca
const search_strategy = {
    none: "none",
    radar: "radar"
}

// Enum com estratégias de perseguição
const chase_strategy = {
    standard: "standard"
}

// Define a cor do botão das estratégias disponíveis
var strategies_color = "#868686";

// Define a cor do botão das estratégias selecionadas
var selected_strategy_color = "#008080";

// Redefine os botões dos seletores para a cor padrão -> Não selecionado
function clearButtons(buttons) {
    let type;
    switch (buttons) {
        case mode_selector:
            type = "mode";
            break;
        case initial_move_strategy:
            type = "initial";
            break;
        case search_strategy:
            type = "search";
            break;
        case chase_strategy:
            type = "chase";
            break;
    }
    for (let move in buttons) {
        document.getElementById(type + "_" + move).style.backgroundColor = strategies_color;
    }
}

// Envia um request pro robô para alterar sua configuração de estratégias
// strategyType -> Qual tipo de estratégia está sendo alterada
// strategy     -> Nova estratégia a ser selecionada  
function setStrategy(strategyType, strategy) {
    let type;
    switch (strategyType) {
        case strategy_type.mode:
            type = "mode";
            clearButtons(mode_selector)
            break;
        case strategy_type.initial:
            type = "initial";
            clearButtons(initial_move_strategy);
            break;
        case strategy_type.search:
            type = "search";
            clearButtons(search_strategy);
            break;
        case strategy_type.chase:
            type = "chase";
            clearButtons(chase_strategy);
            break;
    }
    connection.send('{ "' + type + '" : "' + strategy + '" }');
}

//Envia um request para a máquina do robô emitir um evento específico
function requestEvent(event) {
    connection.send('{ "event_request" : "' + event + '" }');
}

// Atualiza visulmente na tela para quais estratégias o robô está atualmente configurado
function updateRobotConfigurations(type, strategy) {
    switch (type) {
        case strategy_type.mode:
            clearButtons(mode_selector)
        case strategy_type.initial:
            clearButtons(initial_move_strategy);
            break;
        case strategy_type.search:
            clearButtons(search_strategy);
            break;
        case strategy_type.chase:
            clearButtons(chase_strategy);
            break;
    }
    document.getElementById(type + "_" + strategy).style.backgroundColor = selected_strategy_color;
}

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

// Quando recebe-se dados do robô
connection.onmessage = function(response) {
    let json = JSON.parse(response.data);

    // Verifica as chaves contidas no JSON recebido
    if ("robot_name" in json) {
        document.getElementById("connection-status-text").innerHTML = "Connected to " + json["robot_name"];
    }

    // Recebendo Array de estratégias
    if ("configurations" in json) {
        let mode_configured;
        switch (json["configurations"]["mode"]) {
            case "auto":
                mode_configured = mode_selector.auto;
                break;
            case "rc":
                mode_configured = mode_selector.rc;
                break;
        }
        updateRobotConfigurations(strategy_type.mode, mode_configured);

        let initial_move_configured;
        switch (json["configurations"]["initial_move"]) {
            case "none":
                initial_move_configured = initial_move_strategy.none;
                break;
            case "full_frente":
                initial_move_configured = initial_move_strategy.full_frente;
                break;
            case "zig_zag":
                initial_move_configured = initial_move_strategy.zig_zag;
                break;
        }
        updateRobotConfigurations(strategy_type.initial, initial_move_configured);

        let search_configured;
        switch (json["configurations"]["search"]) {
            case "none":
                search_configured = search_strategy.none;
                break;
            case "radar":
                search_configured = search_strategy.radar;
                break;
        }
        updateRobotConfigurations(strategy_type.search, search_configured);

        let chase_configured;
        switch (json["configurations"]["chase"]) {
            case "standard":
                chase_configured = chase_strategy.standard;
                break;
        }
        updateRobotConfigurations(strategy_type.chase, chase_configured);
    }
}