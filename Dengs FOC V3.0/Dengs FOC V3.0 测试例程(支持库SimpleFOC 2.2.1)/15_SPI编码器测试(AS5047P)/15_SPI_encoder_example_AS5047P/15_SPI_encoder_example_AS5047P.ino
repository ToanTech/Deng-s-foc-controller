// Deng's FOC ABI编码器测试例程 测试硬件：灯哥开源FOC V3.0
// 测试用编码器 AS5047P,SPI


#include <SimpleFOC.h>

#define HSPI_MISO 19 // 对应双路上的SDA_0引脚
#define HSPI_MOSI 23 // 对应双路上的SDA_1引脚
#define HSPI_SCLK 18 // 对应双路上的SCL_0引脚
#define HSPI_SS 5 // 对应双路上的SCL_1引脚


MagneticSensorSPI sensor = MagneticSensorSPI(AS5147_SPI, HSPI_SS);
SPIClass SPI_2(HSPI);


void setup() {
  Serial.begin(115200);
  SPI_2.begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS); //SCLK, MISO, MOSI, SS 
  sensor.init(&SPI_2);
  

  Serial.println("Encoder ready");
  _delay(1000);
}


void loop() {
//  sensor.update(); // 如果simpleFOC库版本为2.2.0及以上需要取消该行注释
  // 输出角度和角速度
  Serial.print(sensor.getAngle());
  Serial.print("\t");
  Serial.println(sensor.getVelocity());
}
