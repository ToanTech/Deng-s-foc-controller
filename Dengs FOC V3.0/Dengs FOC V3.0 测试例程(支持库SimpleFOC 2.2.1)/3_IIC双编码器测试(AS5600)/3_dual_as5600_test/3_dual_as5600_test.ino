// Deng's FOC AS5600测试例程 测试硬件：灯哥开源FOC V3.0

#include <SimpleFOC.h>


MagneticSensorI2C sensor0 = MagneticSensorI2C(AS5600_I2C);
MagneticSensorI2C sensor1 = MagneticSensorI2C(AS5600_I2C);
TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);


void setup() {

  
  Serial.begin(115200);
  _delay(750);

  //针对最新版本ESP-Arduino 2.0.2,采用下面两句
  I2Cone.begin(19,18, 400000UL);   //SDA0,SCL0
  I2Ctwo.begin(23,5, 400000UL);
  
  sensor0.init(&I2Cone);
  sensor1.init(&I2Ctwo);
}

void loop() {
  //_delay(200);
  Serial.print(sensor0.getAngle()); 
  Serial.print(" - "); 
  Serial.print(sensor1.getAngle());
  Serial.println();
}
