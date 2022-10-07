import requests
import time

r = requests.get('http://192.168.4.1/read_speed')
print(r.text)

r = requests.post('http://192.168.4.1/servo_control?angle=150')
time.sleep(1)
r = requests.get('http://192.168.4.1/read_angle')
print(r.text)
