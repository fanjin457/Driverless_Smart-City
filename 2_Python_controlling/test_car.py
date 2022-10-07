import requests
import time

 
r = requests.post('http://192.168.4.1/motor_control?speed=60')
time.sleep(3)
r = requests.post('http://192.168.4.1/motor_control?angle=150')
time.sleep(1)
r = requests.post('http://192.168.4.1/motor_control?speed=60')
time.sleep(3)
r = requests.post('http://192.168.4.1/motor_control?angle=90')
time.sleep(1)
r = requests.post('http://192.168.4.1/servo_control?speed=0')
