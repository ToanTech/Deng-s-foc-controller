// Deng's FOC 电流检测测试例程 测试硬件：灯哥开源FOC V3.0

#include <SimpleFOC.h>

// 电流检测
// 采样电阻值 增益 ADC引脚
InlineCurrentSense current_sense0 = InlineCurrentSense(0.01, 50.0, 39, 36);
InlineCurrentSense current_sense1 = InlineCurrentSense(0.01, 50.0, 35, 34);


void setup() {
  // 电流检测
  current_sense0.init();
  current_sense1.init();

  current_sense0.gain_b *= -1;
  current_sense1.gain_b *= -1;
  
  Serial.begin(115200);
  Serial.println("Current sense ready.");
}

void loop() {

  PhaseCurrent_s currents0 = current_sense0.getPhaseCurrents();
  float current_magnitude0 = current_sense0.getDCCurrent();
  PhaseCurrent_s currents1 = current_sense1.getPhaseCurrents();
  float current_magnitude1 = current_sense1.getDCCurrent();

  Serial.print(currents0.a*1000); // milli Amps
  Serial.print("\t");
  Serial.print(currents0.b*1000); // milli Amps
  Serial.print("\t");
  Serial.print(currents0.c*1000); // milli Amps
  Serial.print("\t");
  Serial.println(current_magnitude0*1000); // milli Amps
  Serial.print(currents1.a*1000); // milli Amps
  Serial.print("\t");
  Serial.print(currents1.b*1000); // milli Amps
  Serial.print("\t");
  Serial.print(currents1.c*1000); // milli Amps
  Serial.print("\t");
  Serial.println(current_magnitude1*1000); // milli Amps
  Serial.println();
}
