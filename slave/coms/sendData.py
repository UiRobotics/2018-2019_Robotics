'''********************************************************************
    sendData.py
    Andrew L
    The template to open an fldigi client and send data through python
********************************************************************'''
import pyfldigi
import hashlib #finding checksum for verification
import time

'''
Standard into box into laptop
Green into insulator into nuc
'''

app = pyfldigi.ApplicationMonitor()
app.start()     # starts fldigi
client = pyfldigi.Client()
client.modem.name = 'BPSK63'    # sets op mode
client.modem.carrier = 2500 #sets cursor frequency

CALL_SIGN = "KD9JTB"
startString = "IDevice:"
endString = ";"
''' ideal message would be like "Idevice:5B:print('wow');"
    
    Recieving Functions:
    opMode(modeName) - changes the op mode to modeName (send as string)
    changeFrequency(frequency) - changes the operating frequency in MHz
    restartFldigi() - restarts the app and client
'''

def safeSendCommand(command):
    checker = hashlib.md5()                                               #
    checker.update(command.encode())                                      # calculating the md5sum of the command
    calculatedSum = (b'%02X' % (sum(checker.digest()) & 0xFF)).decode()   #
    timeOut = 10 + len(command)
    stringToSend = startString + calculatedSum + ':' + command + endString
    client.main.send(stringToSend, timeout=timeOut)
    while not awaitFailure():
        print('Transmition failed - Resending . . .')
        client.main.send(stringToSend, timeout=timeOut)
    print('Good to go on another one cheif')

def fastSendCommand(command):
    timeOut = 10 + len(command)
    stringToSend = startString + 'XX' + ':' + command + endString
    client.main.send(stringToSend, timeout=timeOut)
    print('Good to go on another one cheif')

def awaitFailure():
    t_end = time.time() + 10
    noResponse = True
    buffer = ''
    while (time.time() < t_end) and noResponse:
        curr_buffer = client.text.get_rx_data().decode('UTF-8')
        if len(curr_buffer) != 0:
            buffer += curr_buffer
            if 'BAD' in buffer:
                noResponse = False
                return False
            elif 'GOOD' in buffer:
                noResponse = False
                return True

def yellCallsign():
    client.main.send("de" + (" " + CALL_SIGN)*3 + " k\n", timeout=15)
    client.delay(1500)

def restart():
    global app
    app.kill()
    time.sleep(3)
    app = pyfldigi.ApplicationMonitor()
    app.start()
    client = pyfldigi.Client()
    client.modem.carrier = 2500
    time.sleep(2)
    print("should be restarted")