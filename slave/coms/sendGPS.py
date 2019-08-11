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
    if "Arduino" in a.manufacturer:
        arduino = serial.Serial(a.name, 115200, timeout=.1)

startString = "IDevice:"
endString = ";"
''' ideal message would be like "Idevice:5B:print('wow');"
    opMode(modeName) - changes the op mode to modeName (send as string)
    changeFrequency(frequency) - changes the operating frequency in MHz
    restartFldigi() - restarts the app and client
'''

gpsSendTime = time.clock() - 10

def main():
    global gpsSendTime
    buffer = ''
    while True:
        curr_buffer = client.text.get_rx_data().decode('UTF-8')
        if len(curr_buffer) != 0:
            buffer += curr_buffer
        elif (time.clock() - gpsSendTime) > 15:
            gpsSendTime = time.clock()
            gps()
        if endString in buffer: # only looks for messages in buffer if there's a terminating character in the buffer
            if startString in buffer:
                start = buffer.find(startString)
                end = buffer.find(endString) + len(endString)
                message = buffer[start:end]
                print("message recieved = " + message)#####################################################
                parseM(message)
                buffer = ''
            else: # if theres a terminating character but no start string
                time.sleep(4)
                client.main.send("de BAD k\n", timeout=15)
                buffer = ''
        time.sleep(1)

def rosPost(command):
    try:
        exec(command)
    except: pass

def parseM(message):
    message = message[len(startString):] # removes the starting characters
    sentSum = message[:2]                # gather checksum
    message = message[3:]                # remove checksum from message
    valueEnd = message.find(endString)   # 
    command = message[:valueEnd]         # remove the terminating character from the string
    
    checker = hashlib.md5()                                               #
    checker.update(command.encode())                                      # calculating the md5sum of the command
    calculatedSum = (b'%02X' % (sum(checker.digest()) & 0xFF)).decode()   #

    if sentSum == 'XX':
        rosPost(command)
    elif sentSum == calculatedSum:
        time.sleep(4)
        client.main.send("de GOOD k\n", timeout=15)
        rosPost(command)
    else:
        time.sleep(4)
        client.main.send("de BAD k\n", timeout=15)

def restartFldigi():
    global app
    app.kill()
    time.sleep(3)
    app = pyfldigi.ApplicationMonitor()
    app.start()
    client = pyfldigi.Client()
    client.modem.carrier = 2500
    time.sleep(2)
    client.main.send("de restart successful k/n", timeout=15)

def changeFrequency(freq):
    client.rig.frequency = freq * 1000
    client.modem.carrier = 2500
    time.sleep(1)
    client.main.send("de frequency set to " + str(client.rig.frequency) + " k/n", timeout = 15)

def opMode(modeName):
    client.modem.name = modeName
    client.modem.carrier = 2500
    time.sleep(1)
    client.main.send("de opMode set at " + client.modem.name + " k/n", timeout=15)

def gps():
    rosGPS = 
    client.main.send("de Idevice:" + str(rosGPS[1]) + ":" + str(rosGPS[0]) + "; k\n", timeout = 20)
    time.sleep(1)

main()