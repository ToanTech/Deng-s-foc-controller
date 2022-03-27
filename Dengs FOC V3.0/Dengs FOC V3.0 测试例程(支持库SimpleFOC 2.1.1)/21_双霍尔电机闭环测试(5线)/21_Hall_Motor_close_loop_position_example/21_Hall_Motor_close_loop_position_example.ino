  /**
Deng's FOC 闭环位置控制例程 测试库：SimpleFOC 2.1.1 测试硬件：灯哥开源FOC V3.0
在串口窗口中输入：T+位置，就可以使得两个电机闭环转动
比如让两个电机都转动180°，则输入其弧度制：T3.14
在使用自己的电机时，请一定记得修改默认极对数，即 BLDCMotor()和HallSensor()中的值，设置为自己的极对数数字
程序默认设置的供电电压为 16.8V,用其他电压供电请记得修改 voltage_power_supply , voltage_limit 变量中的值
PID参数按照实际情况自行调制
*/

#include <SimpleFOC.h>
//18——对应板上引脚SCL_0
//19——对应板上引脚SDA_0
//15——对应板上引脚I_0
//1——极对数
HallSensor sensor = HallSensor(18, 19, 15, 1);// U V W 极对数
void doA(){sensor.handleA();}
void doB(){sensor.handleB();}
void doC(){sensor.handleC();}
//5——对应板上引脚SCL_0
//23——对应板上引脚SDA_0
//13——对应板上引脚I_0
//1——极对数
HallSensor sensor1 = HallSensor(5, 23, 13, 1); // U V W 极对数
void doA1(){sensor1.handleA();}
void doB1(){sensor1.handleB();}
void doC1(){sensor1.handleC();}

//电机参数 根据电机设置极对数
BLDCMotor motor = BLDCMotor(1);
BLDCDriver3PWM driver = BLDCDriver3PWM(32, 33, 25, 22);

BLDCMotor motor1 = BLDCMotor(1);
BLDCDriver3PWM driver1 = BLDCDriver3PWM(26, 27, 14, 12);

//命令设置
float target_velocity = 0;
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_velocity, cmd); }

void setup() {
  sensor.init();
  sensor1.init();
  sensor.enableInterrupts(doA, doB, doC);
  sensor1.enableInterrupts(doA1, doB1, doC1);

  
  //连接motor对象与传感器对象
  motor.linkSensor(&sensor);
  motor1.linkSensor(&sensor1);

  //供电电压设置 [V]
  driver.voltage_power_supply = 12;
  driver.init();

  driver1.voltage_power_supply = 12;
  driver1.init();
  //连接电机和driver对象
  motor.linkDriver(&driver);
  motor1.linkDriver(&driver1);

  // aligning voltage [V]
  motor.voltage_sensor_align = 3;
  // index search velocity [rad/s]
  motor.velocity_index_search = 3;
  
  //运动控制模式设置
  motor.controller = MotionControlType::angle;
  motor1.controller = MotionControlType::angle;

  //速度PI环设置
  motor.PID_velocity.P = 0.005;
  motor1.PID_velocity.P = 0.005;
  motor.PID_velocity.I = 0.1;
  motor1.PID_velocity.I = 0.1;
  motor.PID_velocity.D = 0;
  motor1.PID_velocity.D = 0;
  //角度P环设置 
  motor.P_angle.P = 20;
  motor1.P_angle.P = 20;
  //最大电机限制电压
  motor.voltage_limit = 6;
  motor1.voltage_limit = 6;

  motor.PID_velocity.output_ramp = 1000;
  motor1.PID_velocity.output_ramp = 1000;
  
  //速度低通滤波时间常数
  motor.LPF_velocity.Tf = 0.01f;
  motor1.LPF_velocity.Tf = 0.01f;

  //设置最大速度限制
  motor.velocity_limit = 45;
  motor1.velocity_limit = 45;

  Serial.begin(115200);
  motor.useMonitoring(Serial);
  motor1.useMonitoring(Serial);

  
  //初始化电机
  motor.init();
  motor1.init();
  //初始化 FOC
  motor.initFOC();
  motor1.initFOC();
  command.add('T', doTarget, "target velocity");

  Serial.println(F("Motor ready."));
  Serial.println(F("Set the target velocity using serial terminal:"));
}



void loop() {
  motor.loopFOC();
  motor1.loopFOC();

  motor.move(target_velocity);
  motor1.move(target_velocity);

  command.run();
//  sensor.update();
//  sensor1.update();

//  Serial.print(sensor1.getAngle());
//  Serial.print("\t");
//  Serial.println(sensor1.getVelocity());
}
