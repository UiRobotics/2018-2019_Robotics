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
while True:
    curr_message = client.text.get_rx_data().decode('UTF-8').strip()
    print(curr_message)
    time.sleep(2.5)
