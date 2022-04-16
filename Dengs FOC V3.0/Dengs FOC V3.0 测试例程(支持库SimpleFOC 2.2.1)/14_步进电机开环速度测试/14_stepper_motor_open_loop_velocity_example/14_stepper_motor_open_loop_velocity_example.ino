// Deng's FOC 步进电机 开环速度控制例程 测试库：SimpleFOC 2.2.1 测试硬件：灯哥开源FOC V3.0
// 串口中输入"T+数字"设定两个电机的转速，如设置电机以 10rad/s 转动，输入 "T10"，电机上电时默认会以 5rad/s 转动
// 在使用自己的电机时，请一定记得修改默认极对数，即 StepperMotor(50) 中的值，设置为自己的极对数数字
// 程序默认设置的供电电压为 12V,用其他电压供电请记得修改 voltage_power_supply , voltage_limit 变量中的值

#include <SimpleFOC.h>

// Stepper motor instance
StepperMotor motor = StepperMotor(50);
// Stepper driver instance
StepperDriver4PWM driver = StepperDriver4PWM(33, 32,14, 25, 22, 12); // M0_1:A+ M0_2:A- M0_3:B+ M1_0:B- 


// commander interface
Commander command = Commander(Serial);
void onMotor(char* cmd){ command.motor(&motor, cmd); }

void setup() {

  driver.pwm_frequency = 40000;

  driver.voltage_power_supply = 12;
  driver.init();
  motor.linkDriver(&driver);

  //开环控制模式设置
  motor.controller = MotionControlType::velocity_openloop;

  // 初始化串口
  Serial.begin(115200);
  motor.useMonitoring(Serial);

  //初始化
  motor.init();

  // 设置初始target
  motor.target = 5;

  // 增加 T 指令
  command.add('T', onMotor, "motor");

  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");
  
  _delay(1000);
}


void loop() {
  motor.move();

  command.run();

}
