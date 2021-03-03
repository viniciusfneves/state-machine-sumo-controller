/* variaveis com nome das estrategias*/
var none = "none";
var full_frente = "full_frente";
var radar = "radar";

/*Conexão com serviço WebSocket do ESP*/
var connection = new WebSocket("ws://" + location.hostname + ":81");

function set_initial_move_strategy(strategy) {
    console.log("Configurando estratégia de movimento inicial para " + strategy);
    connection.send("{initial_move = " + strategy + "}");
}

function set_search_strategy(strategy) {
    console.log("Configurando estratégia de busca para ${strategy}");
    connection.send("{search = " + strategy + "}");
}