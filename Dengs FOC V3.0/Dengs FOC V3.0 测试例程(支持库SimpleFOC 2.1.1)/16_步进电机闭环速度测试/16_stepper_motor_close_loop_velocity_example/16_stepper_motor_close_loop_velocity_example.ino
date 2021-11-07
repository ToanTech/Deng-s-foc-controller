// Deng's FOC 步进电机 闭环速度控制例程 测试库：SimpleFOC 2.1.1 测试硬件：灯哥开源FOC V3.0
// 串口中输入"T+数字"设定两个电机的转速，如设置电机以 10rad/s 转动，输入 "T10"，电机上电时默认会以 5rad/s 转动
// 在使用自己的电机时，请一定记得修改默认极对数，即 StepperMotor(50) 中的值，设置为自己的极对数数字
// 程序默认设置的供电电压为 12V,用其他电压供电请记得修改 voltage_power_supply , voltage_limit 变量中的值
// 使用步进电机对编码器安装要求较高，建议使用我们提供的安装编码器的模型

#include <SimpleFOC.h>

//Sensor
MagneticSensorI2C sensor0 = MagneticSensorI2C(AS5600_I2C);
TwoWire I2Cone = TwoWire(0);
//Sensor

// Stepper motor instance
StepperMotor motor = StepperMotor(50);
// Stepper driver instance
StepperDriver4PWM driver = StepperDriver4PWM(33, 32,26,27, 22, 12); // M0_1:A+ M0_2:A- M1_1:B+ M1_2:B- 


// commander interface
Commander command = Commander(Serial);
void onMotor(char* cmd){ command.motor(&motor, cmd); }

void setup() {
  I2Cone.begin(23,5, 400000);   //SDA0,SCL0
  sensor0.init(&I2Cone);
  motor.linkSensor(&sensor0);
  motor.voltage_sensor_align=10;
  driver.pwm_frequency = 40000;

  driver.voltage_power_supply = 16.8;
  driver.init();
  motor.linkDriver(&driver);
  //开环控制模式设置
  motor.controller = MotionControlType::velocity;
  
  motor.PID_velocity.P = 0.5;
  motor.PID_velocity.I = 10;
  motor.PID_velocity.D = 0;
  motor.voltage_limit = 6;
  motor.PID_velocity.output_ramp = 1000;
  motor.LPF_velocity.Tf = 0.01f;
  //motor.motion_downsample = 15;



  // 初始化串口
  Serial.begin(115200);
  motor.useMonitoring(Serial);

  //初始化
  motor.init();
  motor.initFOC();

  // 设置初始target
  motor.target = 1;

  // 增加 T 指令
  command.add('T', onMotor, "motor");

  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");
  
  _delay(1000);
}


void loop() {
  sensor0.update();
  //Serial.println(sensor0.getAngle());
  motor.loopFOC();
  motor.move();

  command.run();

}
