// Deng's FOC 步进电机Step Dir信号接收例程 测试库：SimpleFOC 2.2.0 测试硬件：灯哥开源FOC V3.0
// Step信号接驱动板I1,Dir信号接驱动板I0


#include <SimpleFOC.h>

// angle 
float received_angle = 0;

// StepDirListener( step_pin, dir_pin, counter_to_value)
StepDirListener step_dir = StepDirListener(13, 15, 360.0/200.0); // receive the angle in degrees
void onStep() { step_dir.handle(); }

void setup() {

  Serial.begin(115200);
  
  // init step and dir pins
  step_dir.init();
  // enable interrupts 
  step_dir.enableInterrupt(onStep);
  // attach the variable to be updated on each step (optional) 
  // the same can be done asynchronously by caling step_dir.getValue();
  step_dir.attach(&received_angle);
    
  Serial.println(F("Step/Dir listenning."));
  _delay(1000);
}

void loop() {
  Serial.print(received_angle); 
  Serial.print("\t");
  Serial.println(step_dir.getValue());
  //_delay(500);
}
