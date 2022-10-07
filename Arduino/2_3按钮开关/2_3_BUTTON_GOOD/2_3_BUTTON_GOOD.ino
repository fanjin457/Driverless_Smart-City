const int led33 = 33;
const int button34 = 34;
boolean change = false; // 通过按钮来改变change的值

void setup(){
  pinMode(led33,OUTPUT);
  pinMode(button34,INPUT);
  Serial.begin(115200);
}

void loop(){
  /*while 用来暂停程序，保持button的当前状态，按一下按钮退出循环。*/
  while (digitalRead(button34) == HIGH){ 
  }
  
  if (change == true){
    digitalWrite(led33,LOW);// 亮
    change = !change;
  }else{
    digitalWrite(led33,HIGH);// 灭
    change = !change;
  }
  Serial.println(change);
  delay(500);  // 缓冲时间
}
/*这一步至关重要，如果没有 while 来暂停程序、等待输入的话，按钮会失灵，
因为loop循环得很快，你在按下按钮的瞬间，程序首先会退出while循环，
然后执行了很多次loop里的程序，所以在你松开按钮时我们不确定loop
运行的循环是亮着的LED还是熄灭的LED*/
