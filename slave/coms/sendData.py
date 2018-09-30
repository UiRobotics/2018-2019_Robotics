'''********************************************************************
    sendData.py
    Andrew L

    The template to open an fldigi client and send data through python
    Fldigi must already be running
********************************************************************'''

import pyfldigi
import time #for delays if necessary

client = pyfldigi.Client()

client.main.send("") #takes in strings or bytes and sends as bytes
