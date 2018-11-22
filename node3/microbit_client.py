from microbit import *
import radio

#compass.calibrate()
radio.on()

id = 'A'

prev_vector = 0,0,0,0,0,0,0,0

while True:

	vector = button_a.is_pressed(), button_b.is_pressed(),\
		accelerometer.get_x()>256, accelerometer.get_x()<-256,\
		accelerometer.get_y()>256, accelerometer.get_y()<-256,\
		pin0.is_touched(), pin1.is_touched(), pin2.is_touched()
	
	if prev_vector!=vector:
		s = ""
		for v in vector:
			if v:
				s+= '1'
			else:
				s+= '0'	
		radio.send(id+s)
	prev_vector = vector
