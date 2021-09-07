/**
Deng's FOC 闭环位置力矩互控 例程 测试库：SimpleFOC 2.1.1 测试硬件：灯哥开源FOC V1.0
上电后转动其中一个电机，另一个电机也会跟随，两个电机时刻保持位置力矩互控
在使用自己的电机时，请一定记得修改默认极对数，即 BLDCMotor(7) 中的值，设置为自己的极对数数字
程序默认设置的供电电压为 7.4V,用其他电压供电请记得修改 voltage_power_supply , voltage_limit 变量中的值
默认PID针对的电机是 Ipower 4008 ，使用的编码器是AS5600，使用自己的电机需要修改PID参数，才能实现更好效果
 */
 
#include <SimpleFOC.h>


MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
MagneticSensorI2C sensor1 = MagneticSensorI2C(AS5600_I2C);
TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

// Motor instance
BLDCMotor motor = BLDCMotor(7);
BLDCDriver3PWM driver = BLDCDriver3PWM(32, 33, 25, 22);

BLDCMotor motor1 = BLDCMotor(7);
BLDCDriver3PWM driver1 = BLDCDriver3PWM(26, 27, 14, 12);


void setup() {
  I2Cone.begin(18, 5, 400000); 
  I2Ctwo.begin(19, 23, 400000);
  sensor.init(&I2Cone);
  sensor1.init(&I2Ctwo);
  // link the motor to the sensor
  motor.linkSensor(&sensor);
  motor1.linkSensor(&sensor1);

  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 7.4;
  driver.init();

  driver1.voltage_power_supply = 7.4;
  driver1.init();
  // link the motor and the driver
  motor.linkDriver(&driver);
  motor1.linkDriver(&driver1);
  
  // set motion control loop to be used
  motor.controller = MotionControlType::torque;
  motor1.controller = MotionControlType::torque;

  // maximal voltage to be set to the motor
  motor.voltage_limit = 7.4;
  motor1.voltage_limit = 7.4;
  // use monitoring with serial 
  Serial.begin(115200);
  // comment out if not needed
  motor.useMonitoring(Serial);
  motor1.useMonitoring(Serial);
  
  //初始化电机
  motor.init();
  motor1.init();
  motor.initFOC();
  motor1.initFOC();


  Serial.println("Motor ready.");
  _delay(1000);
  
}

void loop() {

  motor.loopFOC();
  motor1.loopFOC();

  motor.move( 5*(motor1.shaft_angle - motor.shaft_angle));
  motor1.move( 5*(motor.shaft_angle - motor1.shaft_angle));
}

float dead_zone(float x){
  return abs(x) < 0.2 ? 0 : x;
}
