import serial.tools.list_ports as SerialLib
import serial

ports = SerialLib.comports()
for a in ports:
    if "Arduino" in a.description:
           ser = serial.Serial( "/dev/"+ a.name, 9600)
           
