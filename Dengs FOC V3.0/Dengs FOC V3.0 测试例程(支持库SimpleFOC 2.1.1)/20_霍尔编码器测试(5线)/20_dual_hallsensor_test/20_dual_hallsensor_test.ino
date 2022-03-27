// Deng's FOC 五线霍尔测试例程 测试硬件：灯哥开源FOC V3.0
#include <SimpleFOC.h>


//编码器实例
//18——对应板上引脚SCL_0
//19——对应板上引脚SDA_0
//15——对应板上引脚I_0
//1——极对数
HallSensor sensor1 = HallSensor(18, 19, 15, 1);
//5——对应板上引脚SCL_0
//23——对应板上引脚SDA_0
//13——对应板上引脚I_0
//1——极对数
HallSensor sensor2 = HallSensor(5, 23, 13, 1);

void doA(){sensor1.handleA();}
void doB(){sensor1.handleB();}
void doC(){sensor1.handleC();}
void doA1(){sensor2.handleA();}
void doB1(){sensor2.handleB();}
void doC1(){sensor2.handleC();}

void setup() {
//  // 编码器设置
//  sensor1.pullup = Pullup::USE_EXTERN;
  
  // 初始化磁传感器硬件
  sensor1.init();
  sensor2.init();
  // 启用硬件中断
  sensor1.enableInterrupts(doA, doB, doC);
  sensor2.enableInterrupts(doA1, doB1, doC1);

  
  Serial.begin(115200);
  

  Serial.println("Sensor ready");
  _delay(1000);


}

void loop() {

  Serial.print(sensor1.getAngle());
  Serial.print("\t");
  Serial.println(sensor2.getAngle());

}
