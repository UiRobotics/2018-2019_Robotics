'''********************************************************************
    sendData.py
    Andrew L
    The template to open an fldigi client and send data through python
********************************************************************'''
import pyfldigi
import hashlib #finding checksum for verification
import time

app = pyfldigi.ApplicationMonitor()
app.start() # starts fldigi
client = pyfldigi.Client()
# sets the op mode and cursor frequency
client.modem.id = 41
client.modem.carrier = 2500

CALL_SIGN = "KD9JTB"

def yellCallsign():
    client.main.send("de" + (" " + CALL_SIGN)*3 + " k\n", timeout=15)
    client.delay(1500)





'''
def md5sum(src, length=io.DEFAULT_BUFFER_SIZE):
    size = os.path.getsize(src)
    calculated = 0
    bytes = hashlib.md5()
    with io.open(src, mode="rb") as file:
        for chunk in iter(lambda: file.read(length), b''):
            bytes.update(chunk)
            calculated += len(chunk)
            #print("{}%".format((calculated/size)*100)) #prints the computation percentage
    return b'%02X' % (sum(bytes.digest()) & 0xFF)

def sendFile(src, length=io.DEFAULT_BUFFER_SIZE):
    client.main.send("IDevice:FileTransfer^r")
    client.main.send("\nFile:" + src +"\n^r")
    with io.open(src, mode="rb") as file:
        for chunk in iter(lambda: file.read(length), b''):
            client.main.send(chunk + b'^r') #TODO get this to wait for send before sending next chunk
    sum = md5sum("wordsTest.txt")
    print (sum)
    client.main.send("\n<end>Checksum:" + sum.decode("utf-8") + "...end\n\n^r")
'''
'''*****************************************************************'''
'''
yellCallsign()

client.main.send("hooplah\n") # takes in strings or bytes and sends as bytes
'''