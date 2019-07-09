#!/usr/bin/python  
import serial
import struct
import time

ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=1000000,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)
 
if(ser.isOpen()):
 print("Serial port is open")

#config the servo
# id = 1

#disable torque and enable writting into the eeprom
message = "\xFF\xFF\x01\x04\x03\x18\x00\xDF"
ser.write(message)

# set lower limit angle 0 (Joint mode)
message = "\xFF\xFF\x01\x05\x03\x06\x00\x00\xF0"
ser.write(message)

# set higher limit angle 4095 (Joint mode)
message = "\xFF\xFF\x01\x05\x03\x08\xFF\x0F\xE0"
ser.write(message)

# rotate to angle 0
print("moving to angle 0")
message = "\xFF\xFF\x01\x05\x03\x1E\x00\x00\xD8"
ser.write(message)

# rotate to angle 2048
time.sleep(2)
print("moving to angle 2048")
message = "\xFF\xFF\x01\x05\x03\x1E\x00\x08\xd0"
ser.write(message)

# rotate to angle 4095
time.sleep(2)
print("moving to angle 4095")
message = "\xFF\xFF\x01\x05\x03\x1E\xff\x0f\xca"
ser.write(message)

time.sleep(1)
ser.close()
print("Serial port is close")

