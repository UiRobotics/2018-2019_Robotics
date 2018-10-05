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

def parseM(message):
    message = message[len(startString):-len(endString)] # removes the starting and terminating characters
    # continue parsing, use command-value (maybe list of touples), will eventually go to ros topics or something


def expectMessage():        # takes in messages recieved by fldigi, strips them of white space, and prints until 'REPLY' is sent
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
                print(message)
                parseM(message)
                buffer = ''

        if "REPLY" in buffer:
            RECIEVING = False

        time.sleep(1) #try not having a delay

def sendData():
    client.main.send("TODO: actually send data")

'''while True:
    expectMessage()
    sendData()'''