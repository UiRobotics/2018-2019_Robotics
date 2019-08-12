'''********************************************************************
    baseGPS.py
    Andrew L
    competition gps for basestation
********************************************************************'''
import pyfldigi
import time
import webbrowser

'''
Standard into box into laptop
Green into insulator into nuc
https://maps.googleapis.com/maps/api/staticmap?center=51.453444,-112.714806&zoom=19&size=2000x1000&maptype=satellite&markers=size:tiny|51.453444,%20-112.714806&key=AIzaSyD-yP3nNmaVoY-GSmxF7xenPg4x_TywtLU
AIzaSyD-yP3nNmaVoY-GSmxF7xenPg4x_TywtLU
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

def parseM(message):
    # 51.453444,-112.714806
    message = message[len(startString):] # removes the starting characters
    valueEnd = message.find(endString)   # 
    command = message[:valueEnd]         # remove the terminating character from the string
    
    midCommand = command.find(':')
    latitude = float(command[:midCommand])
    longitude = float(command[midCommand+1:])
    url = "https://maps.googleapis.com/maps/api/staticmap?center=" + latitude + ',' + longitude + "&zoom=19&size=2000x1000&maptype=satellite&markers=size:tiny|" + latitude + ",%20" + longitude "&key=AIzaSyD-yP3nNmaVoY-GSmxF7xenPg4x_TywtLU"
    webbrowser.open(url)

def main():
    Recieving = True
    buffer = ''
    while Recieving:
        curr_buffer = client.text.get_rx_data()
        if len(curr_buffer) != 0:
            buffer += curr_buffer.decode('UTF-8')
        if endString in buffer: # only looks for messages in buffer if there's a terminating character in the buffer
            if startString in buffer:
                start = buffer.find(startString)
                end = buffer.find(endString) + len(endString)
                message = buffer[start:end]
                print("message recieved = " + message)#####################################################
                parseM(message)
                buffer = ''
            else: # if theres a terminating character but no start string
                buffer = ''
        time.sleep(1)

main()