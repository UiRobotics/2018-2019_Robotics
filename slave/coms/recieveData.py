'''********************************************************************
        recieveData.py
	Andrew L

	The template to open an fldigi client and recieve data through python
	Fldigi must already be running
********************************************************************'''
import pyfldigi
import time # for delays

client = pyfldigi.Client()

# takes in messages recieved by fldigi, strips them of white space, and
# puts them as a string in curr_message
buffer = ''
while True:
    curr_message = client.text.get_rx_data().decode('UTF-8')
    if len(curr_message) != 0:
        buffer += curr_message
    # uses 001 as a terminating character and prints only when 001 is recieved
    if "001" in buffer:
        print(buffer)
        buffer = ''

    time.sleep(1)