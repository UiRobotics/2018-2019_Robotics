'''********************************************************************
    recieveData.py
	Andrew L
	The template to open an fldigi client and recieve data through python
********************************************************************'''
import pyfldigi
import hashlib  #finding checksum for verification
import time

app = pyfldigi.ApplicationMonitor()
app.start()                 # starts fldigi
client = pyfldigi.Client()
client.modem.id = 40       # sets op mode
client.modem.carrier = 2500 # sets cursor frequency

startString = "IDevice:"
endString = ";"
''' ideal message would be like "Idevice:5B:print('wow');"
    opMode - x changes the op mode to x (between 1 and 70something)
    cursFreq - x changes cursor frequency to x (between 31 and 2969)
'''

def rosPost(command):
    print("ros command = " + command)
    try:
        exec(command)
    except: pass

def parseM(message):
    message = message[len(startString):] # removes the starting characters
    checkSum = message[:2]               # gather checksum
    message = message[3:]                # remove checksum from message
    valueEnd = message.find(endString)   # remove the terminating character from the string
    command = message[:valueEnd]
    print(command)
    checker = hashlib.md5()                                               #
    checker.update(command.encode())                                      # calculating the md5sum of the command
    calculatedSum = (b'%02X' % (sum(checker.digest()) & 0xFF)).decode()   #

    print(calculatedSum)
    if checkSum == calculatedSum:
        time.sleep(4)
        client.main.send("de GOOD k\n", timeout=15)
        rosPost(command)
    else:
        time.sleep(4)
        client.main.send("de BAD k\n", timeout=15)


def expectMessage():    # takes in messages recieved by fldigi, strips them of white space, and prints until 'REPLY' is sent
    RECIEVING = True
    buffer = ''
    while RECIEVING:
        curr_buffer = client.text.get_rx_data().decode('UTF-8')
        if len(curr_buffer) != 0:
            buffer += curr_buffer
        if endString in buffer: # only looks for messages in buffer if there's a terminating character in the buffer
            if startString in buffer:
                start = buffer.find(startString)
                end = buffer.find(endString) + len(endString)
                message = buffer[start:end]
                print("message recieved = " + message)#####################################################
                parseM(message)
                buffer = ''
            else: ##################################test######## if theres a terminating character but no start string
                time.sleep(4)
                client.main.send("de BAD k\n", timeout=15)
                buffer = ''

        time.sleep(1) #try not having a delay
expectMessage()

'''while True:
    expectMessage()'''

'''def recieveFile():
    file = open(src,"w+") #fix opening
    buffer = ""
    complete = transfered = False
    while not complete:
        buffer += client.text.get_rx_data().decode('UTF-8')
        if not transfered:
            start = buffer.find(':')
            buffer = buffer[start:]
            end = buffer.find("\n")
            src = buffer[start:end]
            if src == "<end>\n":
                transfered = True;
            else:
                file.write(src)
            buffer = buffer[end:]
        else:
            sum = buffer[9:12]
            #compare sum
    #write to the file, may need to fix buffer
    
    file.close()
'''