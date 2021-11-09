"""my_controller controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from inputs import devices, get_gamepad
from controller import Robot, Joystick

def map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
# create the Robot instance.
robot = Robot()
xbox = Joystick()

# get the time step of the current world.
timestep = 64

left_motor = robot.getDevice("left wheel motor")
right_motor = robot.getDevice("right wheel motor")

left_motor.setPosition(float("inf"))
right_motor.setPosition(float("inf"))

xbox.enable(timestep)
# You should insert a getDevice-like function in order to get the
# instance of a device of the robot. Something like:
#  motor = robot.getMotor('motorname')
#  ds = robot.getDistanceSensor('dsname')
#  ds.enable(timestep)

def driveRobot(linearSpeed, angularSpeed):

    linearSpeed *= 36.25*1.3
    angularSpeed *= (2*36.25/132)/2
    
    PWM_left  = ((2 * linearSpeed + angularSpeed * (132)) / (2 * (36.25))) * 100
    PWM_right = ((2 * linearSpeed - angularSpeed * (132)) / (2 * (36.25))) * 100

    if PWM_left > PWM_right:
        maxSpeed = PWM_left
    else:
        maxSpeed = PWM_right
        
    if PWM_left < PWM_right:
        minSpeed = PWM_left
    else:
        minSpeed = PWM_right

    if maxSpeed > 100:
        PWM_left -= maxSpeed - 100;
        PWM_right -= maxSpeed - 100;
    elif minSpeed < -100:
        PWM_left -= minSpeed + 100;
        PWM_right -= minSpeed + 100;
        
    left_motor.setVelocity(PWM_left)
    right_motor.setVelocity(PWM_right)

def getAxis():

    CH2 = xbox.getAxisValue(5)
    CH2 = round(map(CH2, 0,32768,-1,1),2)
    
    CH1 = xbox.getAxisValue(1)
    CH1 = round(map(CH1, -32768,32768,-1,1),2)

    CH3 = xbox.getAxisValue(4)*-1
    CH3 = round(map(CH3, 0,32768,-1,1),2)
    
    accel = (CH2 + CH3) /2 + 1
    
   # print("ACELL: {}, VOLANT: {}".format(accel, CH1))
    if CH1 > 0 and CH1 < 0.11:
        CH1 = 0
    if CH1 < 0 and CH1 > -0.11:
        CH1 =0
    
    return accel, CH1

# Main loop:
# - perform simulation steps until Webots is stopping the controller
while robot.step(timestep) != -1:
    # Read the sensors:
    # Enter here functions to read sensor data, like:
    #  val = ds.getValue()
    linear, angular = getAxis()
    print(linear, angular)
    #left, right = getWheelMove(angular, linear)
    #left_motor.setVelocity(left*20)
    #right_motor.setVelocity(right*20)
    driveRobot(linear, angular)
    
    
    # Process sensor data here.

    # Enter here functions to send actuator commands, like:
    #  motor.setPosition(10.0)
    pass

# Enter here exit cleanup code.
