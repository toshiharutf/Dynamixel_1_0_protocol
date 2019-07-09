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

#config the servo for wheel mode, both limits at 0
# set lower limit angle 0 (Joint mode)
message = "\xFF\xFF\x01\x05\x03\x06\x00\x00\xF0"
ser.write(message)

# set higher limit angle 0 (Joint mode)
message = "\xFF\xFF\x01\x05\x03\x08\x00\x00\xEE"
ser.write(message)

print("rotate CCW at speed 100")
message = "\xFF\xFF\x01\x05\x03\x20\x64\x00\x72"
ser.write(message)
time.sleep(2)

print("rotate CCW at speed 400")
message = "\xFF\xFF\x01\x05\x03\x20\x90\x01\x45"
ser.write(message)
time.sleep(2)

print("rotate CCW at speed 1023")
message = "\xFF\xFF\x01\x05\x03\x20\xFF\x03\xD4"
ser.write(message)
time.sleep(2)

print("rotate CW at speed 1125")
message = "\xFF\xFF\x01\x05\x03\x20\x65\x04\x6D"
ser.write(message)
time.sleep(2)

print("rotate CW at speed 1425")
message = "\xFF\xFF\x01\x05\x03\x20\x91\x05\x40"
ser.write(message)
time.sleep(2)

print("rotate CW at speed 2047")
message = "\xFF\xFF\x01\x05\x03\x20\xFF\x07\xD0"
ser.write(message)
time.sleep(2)

print("Stopping motor")
message = "\xFF\xFF\x01\x05\x03\x20\x00\x00\xd6"
ser.write(message)

time.sleep(1)
ser.close()
print("Serial port is close")

