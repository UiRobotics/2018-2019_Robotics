import os
import subprocess

cmd_output = subprocess.check_output("lsusb | grep Realtek", shell=True)

output_list = cmd_output.decode().split('\n')

def parser(string):
    string = str(string)
    bus = string.split()[1]
    device = string.split()[3]
    return bus, device

for device in output_list:
    if device !='' :
        output = parser(device)
        cmd = './usbreset /dev/bus/usb/' + output[0] + '/' + output[1]
        os.system(cmd)
