from microbit import *
import radio

radio.on()

while True:    
    try:
        incoming = radio.receive()
        if not incoming is None:
            uart.write(incoming+"\n") 
    except:
            pass
