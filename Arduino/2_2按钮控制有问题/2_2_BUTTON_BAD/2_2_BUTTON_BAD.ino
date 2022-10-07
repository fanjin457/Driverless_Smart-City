const int led33 = 33;
const int button34 = 34;
boolean change = false; // 通过按钮来改变change的值

void setup(){
  pinMode(led33,OUTPUT);
  pinMode(button34,INPUT);
}

void loop(){
  if (digitalRead(button34) == LOW) {
    if (change == true){
      digitalWrite(led33,LOW);// 亮
      change = !change;
    }else{
      digitalWrite(led33,HIGH);// 灭
      change = !change;
    }
  }
}
/* 有问题
