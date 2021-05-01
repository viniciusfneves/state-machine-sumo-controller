from win_controller import *
from send_commands import *
import time

# Define de quanto em quanto tempo os comandos devem ser atualizados no robô
taxa_de_atualizacao = 30    # Em milissegundos

payload = {"linear": 0, "angular": 0}

def initMessage():
    print("Conectando")

def main():
    global payload

    calibrated = False

    controller = Joystick()         # cria o objeto do controlle com multi-threading

    controller.start()              # Inicia o serviço de threads -> Roda em looping

    while True:
        # É necessário pimeiramente mover o stick esquerdo para que ele comece a ler os valores corretos
        # Essa função garante a execução do código após a leitura estar 100% correta
        if(calibrated == False):
            initMessage()
            print("Calibrando controle...")
            print("Mova o Stick esquerdo para os lados para calibrar")
            while(controller.angularSpeed != -1):
                pass
            while(controller.angularSpeed != 1):
                pass
            calibrated = True
        print("Calibrado!\nEnviando comandos...")

        payload["linear"] = controller.linearSpeed
        payload["angular"] = controller.angularSpeed

        # Envia as informações para o robô via http
        status = send_commands(payload)

        # Caso haja uma falha na mensagem, informa ao usuário pelo terminal
        if status == False:
            print("Falha no envio da mensagem")

        # Botão Start encerra o programa e envia comando para parar os motores
        if controller.Start == 1:
            print("Comandando parada...")
            payload["linear"] = 0
            payload["angular"] = 0
            # Continua enviando sinal de parada dos motores até que recebe uma confirmação do robô que o sinal foi interpretado corretamente
            while (send_commands(payload) == False):
                pass
            print("Exiting!")
            break

        time.sleep(taxa_de_atualizacao/1000)

    exit()


if __name__ == "__main__":
    main()
