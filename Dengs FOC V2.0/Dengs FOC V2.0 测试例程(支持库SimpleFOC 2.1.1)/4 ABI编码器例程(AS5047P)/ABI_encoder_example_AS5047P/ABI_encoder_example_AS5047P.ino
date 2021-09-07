// Deng's FOC ABI编码器测试例程 测试硬件：灯哥开源FOC V2.0
// 测试用编码器 AS5047P,CPR=4000


#include <SimpleFOC.h>

//针对ABI接口（0）号
//Encoder encoder = Encoder(19,18,1000,15); //A0;B0;编码器PPR,PPR=CPR/4;I0

//针对ABI接口（1）号
Encoder encoder = Encoder(23,5,1000,13); //A1;B1;编码器PPR,PPR=CPR/4;I1

void doA(){encoder.handleA();}
void doB(){encoder.handleB();}

void setup() {
  Serial.begin(115200);
  encoder.quadrature = Quadrature::ON;
  encoder.pullup = Pullup::USE_EXTERN;

  encoder.init();
  // 硬件中断使能
  encoder.enableInterrupts(doA, doB);

  Serial.println("Encoder ready");
  _delay(1000);
}

void loop() {
  // 输出角度和角速度
  Serial.print(encoder.getAngle());
  Serial.print("\t");
  Serial.println(encoder.getVelocity());
}
