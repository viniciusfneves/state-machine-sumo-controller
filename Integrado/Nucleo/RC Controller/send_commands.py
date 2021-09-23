import requests

# Envia um request de POST no endereço do ESP32 responsável pelo recebimento dos comandos do controle
# Retorna True caso o recebimento tenha sido bem sucedido e False caso tenha ocorrido algum erro
def send_commands(payload):
    r = requests.post("http://192.168.4.1/controller", json=payload)
    if r.status_code != 200:
        return False
    return True
