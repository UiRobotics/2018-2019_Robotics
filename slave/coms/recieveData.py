'''********************************************************************
    recieveData.py
	Andrew L
	The template to open an fldigi client and recieve data through python
********************************************************************'''
import pyfldigi
import time

app = pyfldigi.ApplicationMonitor()
app.start()                 # starts fldigi
client = pyfldigi.Client()
client.modem.id = 42        # sets op mode
client.modem.carrier = 2500 # sets cursor frequency

startString = "IDevice:"
endString = ";"
''' ideal message would be like "Idevice:motor1-23:gps-3490;"
    opMode - x changes the op mode to x (between 1 and 70something)
    cursFreq - x changes cursor frequency to x (between 31 and 2969)
'''

def rosPost(commandPair):
    print(commandPair)

def parseM(message):
    message = message[len(startString):] # removes the starting characters
    # will eventually go to ros topics or something

    commands = []
    while len(message) != 0:    # extrapolate the commands and values into a list(commands) of touples
        valueEnd = message.find(':')
        comValue = message[:valueEnd]
        mid = comValue.find('-')
        if mid != -1:
            commands.append((comValue[:mid],comValue[mid+1:]))
        else:
            commands.append((comValue,''))
        if valueEnd != -1:
            message = message[valueEnd + 1:]
        else:
            message = ""

    for comPair in commands:    # interperate coms commands and export the rest
        if comPair[0] == "opMode":
            client.main.send("switchingOp")
            client.modem.id = comPair[1]
        elif comPair[0] == "cursFreq":
            client.main.send("switchingCurs")
            client.modem.carrier = comPair[1]
        else:
            rosPost(comPair)
    print(commands) ##############################################################


def expectMessage():    # takes in messages recieved by fldigi, strips them of white space, and prints until 'REPLY' is sent
    RECIEVING = True
    buffer = ''
    while RECIEVING:
        curr_buffer = client.text.get_rx_data().decode('UTF-8').strip()
        if len(curr_buffer) != 0:
            buffer += curr_buffer
        if endString in buffer: # only looks for messages in buffer if there's a terminating character in the buffer
            start = buffer.find(startString)
            end = buffer.find(endString) + len(endString) -1
            if not start == -1:
                message = buffer[start:end]
                print(message)#####################################################
                parseM(message)
                buffer = ''

        time.sleep(1) #try not having a delay

def sendData():
    client.main.send("TODO: actually send data")

'''while True:
    expectMessage()
    sendData()'''

#def recieveFile():
#    file = open(src,"w+") #fix opening
#    buffer = ""
#    complete = transfered = False
#    while not complete:
#        buffer += client.text.get_rx_data().decode('UTF-8')
#        if not transfered:
#            start = buffer.find(':')
#            buffer = buffer[start:]
#            end = buffer.find("\n")
#            src = buffer[start:end]
#            if src == "<end>\n":
#                transfered = True;
#            else:
#                file.write(src)
#            buffer = buffer[end:]
#        else:
#            sum = buffer[9:12]
#            #compare sum
#    #write to the file, may need to fix buffer
#    
#
#    file.close()