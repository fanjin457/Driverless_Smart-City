//https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/ledc.html

// servo pwm input pin
const int pwm_pin = 33;  // pwm脉冲宽度调制

// setting PWM properties
const int freq = 1000;  // 频率
const int pwm_channel = 0;  
const int resolution = 8;  // 分辨率

void setup() {
  // put your setup code here, to run once:
  // configure PWM functionalities
  ledcSetup(pwm_channel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwm_pin, pwm_channel);  // 输出 
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int duty_cycle=0; duty_cycle<=255; duty_cycle+=5){
    ledcWrite(pwm_channel, duty_cycle);  // 连续变换电压，占空比参数
    delay(50);
  }
  for (int duty_cycle=255; duty_cycle>=0; duty_cycle-=5){
    ledcWrite(pwm_channel, duty_cycle);
    delay(50);
  }
}
