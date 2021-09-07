/**
灯哥 Py-apple dog project--无刷四足机器人 Deng'FOC 端程序
具体使用方法请见无刷狗 Github：
https://github.com/ToanTech/py-apple-bldc-quadruped-robot
在使用自己的电机时，请一定记得修改默认极对数，即 BLDCMotor(7) 中的值，设置为自己的极对数数字
程序默认设置的供电电压为 7.4V,用其他电压供电请记得修改 voltage_power_supply , voltage_limit 变量中的值
默认PID针对的电机是 Ipower 4008 ，使用自己的电机需要修改PID参数，才能实现更好效果
 */
#include <SimpleFOC.h>
double init_p_sensor=0;
double init_p_sensor1=0;
int commaPosition;                //存储还没有分离出来的字符串 
double motor1_angle,motor2_angle;

MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
MagneticSensorI2C sensor1 = MagneticSensorI2C(AS5600_I2C);
TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

// Motor instance
BLDCMotor motor = BLDCMotor(7);
BLDCDriver3PWM driver = BLDCDriver3PWM(32, 33, 25, 22);

BLDCMotor motor1 = BLDCMotor(7);
BLDCDriver3PWM driver1 = BLDCDriver3PWM(26, 27, 14, 12);

//HardwareSerial Serial2(2);
//定义 TROT 步态变量
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
  driver.voltage_power_supply = 16.8;
  driver.init();

  driver1.voltage_power_supply = 16.8;
  driver1.init();
  // link the motor and the driver
  motor.linkDriver(&driver);
  motor1.linkDriver(&driver1);
  
  // choose FOC modulation (optional)
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
  motor1.foc_modulation = FOCModulationType::SpaceVectorPWM;
  // set motion control loop to be used
  motor.controller = MotionControlType::angle;
  motor1.controller = MotionControlType::angle;

  // contoller configuration 
  // default parameters in defaults.h

  // velocity PI controller parameters
  motor.PID_velocity.P = 0.2;
  motor1.PID_velocity.P = 0.2;
  motor.PID_velocity.I = 20;
  motor1.PID_velocity.I = 20;
  // maximal voltage to be set to the motor
  motor.voltage_limit = 16.8;
  motor1.voltage_limit = 16.8;
  
  // velocity low pass filtering time constant
  // the lower the less filtered
  motor.LPF_velocity.Tf = 0.01;
  motor1.LPF_velocity.Tf = 0.01;

  // angle P controller 
  motor.P_angle.P = 20;
  motor1.P_angle.P = 20;
  // maximal velocity of the position control
  motor.velocity_limit = 40;
  motor1.velocity_limit = 40;

  // use monitoring with serial 
  Serial.begin(115200);
  Serial2.begin(921600);
  // comment out if not needed
  motor.useMonitoring(Serial);
  motor1.useMonitoring(Serial);
  //记录无刷初始位置

  
  // initialize motor
  motor.init();
  motor1.init();
  // align sensor and start FOC
  motor.initFOC();
  motor1.initFOC();

  _delay(1000);
  Serial.println("Motor ready.");
  init_p_sensor=sensor.getAngle();
  init_p_sensor1=sensor1.getAngle();
  Serial.println(init_p_sensor);
  Serial.println(init_p_sensor1);
  
}

String serialReceiveUserCommand() {
  
  // a string to hold incoming data
  static String received_chars;
  
  String command = "";

  while (Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read();
    // add it to the string buffer:
    received_chars += inChar;

    // end of user input
    if (inChar == '\n') {
      
      // execute the user command
      command = received_chars;

      commaPosition = command.indexOf(',');//检测字符串中的逗号
      if(commaPosition != -1)//如果有逗号存在就向下执行
      {
          motor1_angle = command.substring(0,commaPosition).toDouble();            //电机角度
          motor2_angle = command.substring(commaPosition+1, command.length()).toDouble();//打印字符串，从当前位置+1开始
          //Serial.println(motor1_angle);
          //Serial.println(motor2_angle);
      }
      // reset the command buffer 
      received_chars = "";
    }
  }
  return command;
}


void loop() {
  motor.loopFOC();
  motor1.loopFOC();
  motor.move(-init_p_sensor-motor1_angle);
  motor1.move(-init_p_sensor1-motor2_angle); 
  serialReceiveUserCommand();
}
