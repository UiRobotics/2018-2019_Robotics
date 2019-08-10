import serial.tools.list_ports as SerialLib
import serial
import subprocess
import time

nameCounter = 0
ports = SerialLib.comports()
for a in ports:
    nameCounter += 1
    ##print(a.location)
    if "Arduino" in a.manufacturer:
	rosCommand = "rosrun rosserial_python serial_node.py /dev/" + a.name + " __name:=arduino" + str(nameCounter) + " _baud:=115200"
	subprocess.Popen(['gnome-terminal', '-e', rosCommand])

time.sleep(4)
print('goodnight')
