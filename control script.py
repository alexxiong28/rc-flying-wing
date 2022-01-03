import time
import keyboard
import serial

a = 0
b = 127
c = 127
cnt = 0
n = 20
fallrate = 50

readval = "empty"

arduino = serial.Serial(port='COM5', baudrate=115200, timeout = .1)

def write_read(x):
    arduino.write(x.encode())
    print("data sent")
    time.sleep(0.01)
    data = arduino.readline()
    return data
    

while True:
    cnt += 1
    T = keyboard.is_pressed('space')
    P = keyboard.is_pressed('up')-keyboard.is_pressed('down')
    R = keyboard.is_pressed('right')-keyboard.is_pressed('left')
    a += T*n
    if T|(cnt%n)==0:
        a -= 1*fallrate
    b += P*n
    if b-127 and P|(cnt%n) == 0:
        b -= ((b-127)//abs(b-127))
    c += R*n
    if c-127 and R|(cnt%n) == 0:
        c -= ((c-127)//abs(c-127))
    if(keyboard.is_pressed('up') == False and keyboard.is_pressed('down') == False):
        b = 127
    if(keyboard.is_pressed('right') == False and keyboard.is_pressed('left') == False):
        c = 127
    if(keyboard.is_pressed('Q')== True):
        a = 0
    a = min(max(0, a), 255)
    b = min(max(0, b), 255)
    c = min(max(0, c), 255)
    s = "T{}P{}R{}".format(a,b,c)
    readval = write_read(s)
    print(s)
    print("received: ",readval)
                                              
