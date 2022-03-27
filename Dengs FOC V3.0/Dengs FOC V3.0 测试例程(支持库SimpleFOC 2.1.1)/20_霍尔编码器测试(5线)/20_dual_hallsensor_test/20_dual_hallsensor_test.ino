// Deng's FOC 五线霍尔测试例程 测试硬件：灯哥开源FOC V3.0
// 请根据实际情况修改极对数，voltage_supply voltage_limit等参数
#include <SimpleFOC.h>

//电机实例
BLDCMotor motor1 = BLDCMotor(1);
BLDCDriver3PWM driver1 = BLDCDriver3PWM(32, 33, 25, 22);

BLDCMotor motor2 = BLDCMotor(1);
BLDCDriver3PWM driver2  = BLDCDriver3PWM(26, 27, 14, 12);

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
  motor1.linkSensor(&sensor1);
  motor2.linkSensor(&sensor2);
  
  // 驱动器设置
  driver1.voltage_power_supply = 12;
  driver1.init();
  motor1.linkDriver(&driver1);
  Serial.begin(115200);
  

  Serial.println("Sensor ready");
  _delay(1000);
  driver2.voltage_power_supply = 12;
  driver2.init();
  motor2.linkDriver(&driver2);

}

void loop() {

  Serial.print(sensor1.getAngle());
  Serial.print("\t");
  Serial.println(sensor2.getAngle());

}
