const int servo = 13;  //舵机
const int motorA = 26;  //电机A
const int motorB = 27;  //电机B
//PWM
const int freq = 50;  //频率 
const int resolution = 8;  //分辨率
//通道
const int servo_channel = 0;
const int motorA_channel = 1;
const int motorB_channel = 2;

void setup(){
  ledcSetup(servo_channel,freq,resolution);
  ledcAttachPin(servo,servo_channel);
  ledcSetup(motorA_channel,freq,resolution);
  ledcAttachPin(motorA,motorA_channel);
  ledcSetup(motorB_channel,freq,resolution);
  ledcAttachPin(motorB,motorB_channel);

  ledcWrite(servo_channel,20);  //舵机初始化，90°为20,取值范围7~32
  ledcWrite(motorA_channel,0);  //A前进
  ledcWrite(motorB_channel,0);  //B后退
}

void loop(){
  while (1){
    ledcWrite(motorA_channel,200);  //速度0~255
    delay(3000);
    ledcWrite(servo_channel,7);
    delay(1000);
    ledcWrite(motorA_channel,200);
    delay(3000);
    ledcWrite(servo_channel,20);
    delay(1000);
  }
}
