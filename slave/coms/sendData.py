'''********************************************************************
    sendData.py
    Andrew L
    The template to open an fldigi client and send data through python
********************************************************************'''
import pyfldigi
import time

app = pyfldigi.ApplicationMonitor()
app.start() # starts fldigi
client = pyfldigi.Client()
# sets the op mode and cursor frequency
client.modem.id = 42
client.modem.carrier = 2500

CALL_SIGN = "KD9JTB"

def yellCallsign():
    client.main.send("de" + (" " + CALL_SIGN)*3 + " k\n", timeout=15)
    #client.main.abort()

'''*****************************************************************'''

yellCallsign()

client.main.send("hooplah") # takes in strings or bytes and sends as bytes
