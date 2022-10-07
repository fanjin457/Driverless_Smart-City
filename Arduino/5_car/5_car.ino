int djb = 13; //舵机 控制
int djz = 26; //电机 正传
int djf = 27; //电机 反转
int led1= 32; //指示灯-绿色
int led2= 33; //指示灯-红色

void setup()  //基本设置程序
{
  pinMode(led1,OUTPUT);  //指示灯
  pinMode(led2,OUTPUT);  //指示灯

  pinMode(djb,OUTPUT);   //舵机控制（小车方向）
  ledcSetup(0,50,8);     //设置PWM（脉冲宽度）（通道0，50hz-周期20ms，分辨率2**8=256）
  ledcAttachPin(djb,0);  //建立通道0 与端口13(舵机)的连接

  pinMode(djb,OUTPUT);   //电机正转（小车前进）
  ledcSetup(1,50,8);     //设置PWM（脉冲宽度）（通道1，50hz-周期20ms，分辨率2**8=256）
  ledcAttachPin(djz,1);  //建立通道1 与端口26(舵机)的连接

  pinMode(djb,OUTPUT);   //电机反转（小车后退）
  ledcSetup(2,50,8);     //设置PWM（脉冲宽度）（通道2，50hz-周期20ms，分辨率2**8=256）
  ledcAttachPin(djf,2);  //建立通道2 与端口27(舵机)的连接  

  ledcWrite(0,20);       //舵机（通道0）初始化  20中位  7最左  32最右
  ledcWrite(1,0);        //电机正转（通道1） 0停止 256最快速度（全速前进）
  ledcWrite(2,0);        //电机反转（通道2） 0停止 256最快速度（全速后退）

}

void loop() //主程序
{ 
  digitalWrite(led1,0);//点亮绿灯
  digitalWrite(led2,0);//点亮红灯
  ledcWrite(0,7);      //舵机转向最左边
  ledcWrite(1,100);    //电机前进
  ledcWrite(2,0);

  delay(1000);         //延时1秒
    
  digitalWrite(led1,1);//熄灭绿灯
  digitalWrite(led2,1);//熄灭红灯
  ledcWrite(0,32);     //舵机转向最左边
  ledcWrite(1,0);      
  ledcWrite(2,100);    //电机后退

  delay(1000);         //延时1秒  
  
}
