'''********************************************************************
    sendGPS.py
	Andrew L
	competition gps for rover
********************************************************************'''
import pyfldigi
import hashlib  #finding checksum for verification
import time
import serial
import serial.tools.list_ports as SerialLib

app = pyfldigi.ApplicationMonitor()
app.start()                 # starts fldigi
client = pyfldigi.Client()
client.modem.name = 'BPSK63'       # sets op mode (likely switch to 59)
client.modem.carrier = 2500 # sets cursor frequency

ports = SerialLib.comports()
for a in ports:
    if "Arduino" in a.manufacturer and a.pid == 67:
        arduino = serial.Serial(a.name, 115200, timeout=.1)

startString = "IDevice:"
endString = ";"
''' ideal message would be like "Idevice:5B:print('wow');"
    opMode(modeName) - changes the op mode to modeName (send as string)
    changeFrequency(frequency) - changes the operating frequency in MHz
    restartFldigi() - restarts the app and client
'''

gpsSendTime = time.clock() - 5

def main():
    global gpsSendTime
    while True:
        try:
            if (time.clock() - gpsSendTime) > 10:
                gpsSendTime = time.clock()
                gps()
            time.sleep(1)
        except:
            restartFldigi()

def restartFldigi():
    global app
    app.kill()
    time.sleep(3)
    app = pyfldigi.ApplicationMonitor()
    app.start()
    client = pyfldigi.Client()
    client.modem.carrier = 2500
    time.sleep(2)

def changeFrequency(freq):
    client.rig.frequency = freq * 1000
    client.modem.carrier = 2500
    time.sleep(1)

def opMode(modeName):
    client.modem.name = modeName
    client.modem.carrier = 2500
    time.sleep(1)

def gps():
    data = arduino.readline()[:-2] #the last bit gets rid of the new-line chars
	if data:
        rosGPS = (data[:10], data[11:])
        client.main.send("de Idevice:" + str(rosGPS[1]) + ":" + str(rosGPS[0]) + "; k\n", timeout = 20)
    else:
        client.main.send("de no GPS k\n", timeout = 10)
    time.sleep(1)

main()