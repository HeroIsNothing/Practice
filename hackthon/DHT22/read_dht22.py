#https://blog.csdn.net/qq_19961917/article/details/82888111

import Adafruit_DHT
sensor = Adafruit_DHT.DHT22
pin = 4

while True:
	try:
		hu, temp = Adafruit_DHT.read_retry(sensor, pin)
		print('temp: {0:0.1f} hu:{1}'.format(temp, hu))

	except RuntimeError as e:
		print("error\n{0}".format(e))

	except:
		print("error\nFailed to read sensor data!")
