import serial
import time

arduino = serial.Serial(port='COM5', baudrate=9600, timeout=.1) 
#n is saying what to read
def serial_read(n):
    arduino.write(bytes(n, 'utf-8'))
    #era o problema cand nu avea ce sa citeasca
    #time.sleep(0.2)
    data = arduino.readline().decode('utf-8')  # Decode bytes to string using utf-8
    
    return data

def serial_write(x):
    for element in x:
        arduino.write(bytes(element, 'utf-8'))
    return 1