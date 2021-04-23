from threading import Thread
from inputs import get_gamepad

## --> Altere aqui a dead-zone do controle <-- ##
dead_zone = 10  #em porcentagem

##---> NÃO MEXER <---##
max_input = 32768 # não mexer

dead_zone_size = max_input/dead_zone # não mexer

def map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

# Mixa o canal da velocidade linear
def mixLinearChannels(forward_input, backward_input):
    mixedLinearSpeed = forward_input + backward_input*-1
    mixedLinearSpeed = round(map(mixedLinearSpeed, -255, 255, -1, 1), 2)
    return mixedLinearSpeed

# Mixa e aplica dead-zone no comando da velocidade angular
def mixAngularChannels(input):
    if input < dead_zone_size and input > 0:
        mixedAngularSpeed = 0
    elif input > -dead_zone_size and input < 0:
        mixedAngularSpeed = 0
    elif input > 0:
        mixedAngularSpeed = round(map(input, dead_zone_size, max_input, 0, 1), 2)
    else:
        mixedAngularSpeed = round(map(input, -max_input, -dead_zone_size, -1, 0), 2)
    return mixedAngularSpeed


# Classe que lê e armazena os inputs de um controle conectado ao Windows
# Utiliza-se da biblioteca Thread para ler simultâneamente todos os eventos emitidos pelo controle e assim não gerar delay nos comandos
class Joystick(Thread):
    def __init__(self):
        Thread.__init__(self)		# Init da classe Thread -> Não esquecer
        self.A = 0
        self.B = 0
        self.X = 0
        self.Y = 0
        self.LBumper = 0
        self.RBumper = 0
        self.LThumb = 0
        self.RThumb = 0
        self.LTrigger = 0
        self.RTrigger = 0
        self.Back = 0
        self.Start = 0
        self.LStickX = 0
        self.LStickY = 0
        self.RStickX = 0
        self.RStickY = 0
        self.DPadX = 0
        self.DPadY = 0
        self.linearSpeed = 0    # Armazena o dado pré-mixado do controle para velocidade linear
        self.angularSpeed = 0   # Armazena o dado pré-mixado do controle para velocidade angular

    def run(self):		# Função default invocada pela biblioteca Thread
        while True:
            for event in get_gamepad():

                # Categoria de valores binários -> Botões
                if event.ev_type == "Key":
                    if event.code == "BTN_SOUTH":
                        self.A = event.state
                    elif event.code == "BTN_EAST":
                        self.B = event.state
                    elif event.code == "BTN_WEST":
                        self.X = event.state
                    elif event.code == "BTN_NORTH":
                        self.Y = event.state
                    elif event.code == "BTN_TL":
                        self.LBumper = event.state
                    elif event.code == "BTN_TR":
                        self.RBumper = event.state
                    elif event.code == "BTN_THUMBL":
                        self.LThumb = event.state
                    elif event.code == "BTN_THUMBR":
                        self.RThumb = event.state
                    elif event.code == "BTN_START":
                        self.Back = event.state
                    elif event.code == "BTN_SELECT":
                        self.Start = event.state

                # Categoria de valores analógicos -> Triggers e Joysticks
                elif event.ev_type == "Absolute":
                    if event.code == "ABS_Z":
                        self.LTrigger = event.state
                    elif event.code == "ABS_RZ":
                        self.RTrigger = event.state
                    elif event.code == "ABS_X":
                        self.LStickX = event.state
                    elif event.code == "ABS_Y":
                        self.LStickY = event.state
                    elif event.code == "ABS_RX":
                        self.RStickX = event.state
                    elif event.code == "ABS_RY":
                        self.RStickY = event.state
                    elif event.code == "ABS_HAT0Y":
                        self.DPadX = event.state
                    elif event.code == "ABS_HAT0X":
                        self.DPadY = event.state

            # Pré-Mix dos canais
            # Ajusta os valores aos aceitos pelo robô. [-1,1]
            self.linearSpeed = mixLinearChannels(self.RTrigger, self.LTrigger)
            self.angularSpeed = mixAngularChannels(self.LStickX)
