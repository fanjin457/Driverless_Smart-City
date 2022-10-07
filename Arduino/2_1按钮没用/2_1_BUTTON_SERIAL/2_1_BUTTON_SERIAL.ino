const int led32 = 32;
const int button35 = 35;

int buttonstate = 0;

void setup(){
  Serial.begin(115200);
  pinMode(led32,OUTPUT);
  pinMode(button35,INPUT);
  }

void loop(){  // 小灯一直亮，按钮按不按没区别
  buttonstate = digitalRead(button35);
  Serial.println(buttonstate);
}
