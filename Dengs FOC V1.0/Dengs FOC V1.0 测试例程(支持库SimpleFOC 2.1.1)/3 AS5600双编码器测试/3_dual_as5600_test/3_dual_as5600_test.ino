#include <SimpleFOC.h>


MagneticSensorI2C sensor0 = MagneticSensorI2C(AS5600_I2C);
MagneticSensorI2C sensor1 = MagneticSensorI2C(AS5600_I2C);
TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);


void setup() {

  Serial.begin(115200);
  _delay(750);

  I2Cone.begin(18, 5, 400000); 
  I2Ctwo.begin(19, 23, 400000);
  sensor0.init(&I2Cone);
  sensor1.init(&I2Ctwo);
}

void loop() {
  sensor0.update();
  sensor1.update();
  
  //_delay(200);
  Serial.print(sensor0.getAngle()); 
  Serial.print(" - "); 
  Serial.print(sensor1.getAngle());
  Serial.println();
}
