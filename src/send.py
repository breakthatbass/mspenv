import serial
import os
import time
import sys

# usage: mspsend file

if len(sys.argv) != 2:
	print('usage: mspsend [file]')
	sys.exit(1)

fp = sys.argv[1]

try:
	s = serial.Serial('/dev/cu.usbserial-AR0JW545')
	s.write(open(fp, 'rb').read())
	s.write('\r'.encode()) # done signal
	os.system('screen /dev/cu.usbserial-AR1JW545 9600')
except OSError:
	print('error: usb either not found or is already being used')
	print('try unplugging usb and plugging it back in')
	sys.exit(1)
