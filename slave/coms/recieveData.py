'''********************************************************************
    recieveData.py
	Andrew L
	The template to open an fldigi client and recieve data through python
********************************************************************'''
import pyfldigi
import time

app = pyfldigi.ApplicationMonitor()
app.start() # starts fldigi
client = pyfldigi.Client()
# sets the op mode and cursor frequency
client.modem.id = 42
client.modem.carrier = 2500

# takes in messages recieved by fldigi, strips them of white space, and
# puts them as a string in curr_message
buffer = ''
startString = "IDevice"
endString = ";"
while True:
    curr_buffer = client.text.get_rx_data().decode('UTF-8')
    if len(curr_buffer) != 0:
        buffer += curr_buffer
    # uses 001 as a terminating character and prints only when 001 is recieved
    if endString in buffer:
        start = buffer.find(startString)
        end = buffer.find(endString) + len(endString) -1
        message = buffer[start:end]
        print(message)
        buffer = ''

    time.sleep(1)