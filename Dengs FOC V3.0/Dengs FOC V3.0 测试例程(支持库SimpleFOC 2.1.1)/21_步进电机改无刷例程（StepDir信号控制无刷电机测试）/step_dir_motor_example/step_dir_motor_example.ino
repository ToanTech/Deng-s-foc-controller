// Deng's FOC 步进电机 改无刷例程 测试库：SimpleFOC 2.2.0 测试硬件：灯哥开源FOC V3.0
// 无刷电机接在M0口
// Step信号接驱动板I1,Dir信号接驱动板I0
// 编码器默认为AS5600,接SDA_0,SCL_0
// 调整极对数，PID后即可运行

#include <SimpleFOC.h>

// BLDC motor & driver instance
BLDCMotor motor = BLDCMotor(14);
BLDCDriver3PWM driver = BLDCDriver3PWM(32,33,25,22);

// encoder instance
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
TwoWire I2Cone = TwoWire(0);


// StepDirListener( step_pin, dir_pin, counter_to_value)
StepDirListener step_dir = StepDirListener(13, 15, 360.0/200.0); // receive the angle in degrees
void onStep() { step_dir.handle(); }


// inline current sensor instance
// check if your board has R010 (0.01 ohm resistor) or R006 (0.006 mOhm resistor)
InlineCurrentSense current_sense = InlineCurrentSense(0.01, 50.0, 39, 36);

float target_velocity = 0;
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_velocity, cmd); }

void setup() {
  step_dir.init();
  // enable interrupts 
  step_dir.enableInterrupt(onStep);
  //step_dir.attach(&motor.target);
  I2Cone.begin(19,18, 400000); 
  sensor.init(&I2Cone);
  motor.linkSensor(&sensor);
  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 16.8;
  driver.init();
  // link driver
  motor.linkDriver(&driver);

  // TorqueControlType::foc_current
  // 其他模式 TorqueControlType::voltage TorqueControlType::dc_current 
  motor.torque_controller = TorqueControlType::foc_current; 
  // set control loop type to be used
  motor.controller = MotionControlType::angle;

  // contoller configuration based on the controll type 
  motor.PID_velocity.P = 0.2;
  motor.PID_velocity.I = 10;
  motor.PID_velocity.D = 0;
  // default voltage_power_supply
  motor.voltage_limit = 16.8;
  motor.current_limit = 2;
  // velocity low pass filtering time constant
  motor.LPF_velocity.Tf = 0.01;

  // angle loop controller
  motor.P_angle.P = 20;
  // angle loop velocity limit
  motor.velocity_limit = 20;

  // use monitoring with serial for motor init
  // monitoring port
  Serial.begin(115200);
  
  // current sense init and linking
  current_sense.init();
  current_sense.gain_b *= -1;
  motor.linkCurrentSense(&current_sense);

  // initialise motor
  motor.init();
  // align encoder and start FOC
  motor.initFOC(); 
  command.add('T', doTarget, "target velocity");

  // set the inital target value
  motor.target = 0;

  
  _delay(1000);
}


void loop() {
  Serial.println(step_dir.getValue());
  // iterative setting FOC phase voltage
  motor.loopFOC();

  // iterative function setting the outter loop target
  //motor.move(target_velocity);
  motor.move(step_dir.getValue()*3.14/180);
  //command.run();
}
