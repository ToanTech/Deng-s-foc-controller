# 灯哥开源FOC双路无刷电机控制器

​      灯哥开源 FOC 控制器是一个由灯哥开源的，基于 [GPL-3.0](https://github.com/ToanTech/Deng-s-foc-controller/blob/master/LICENSE) 开源协议和ESP32主控的低成本无刷电机双路FOC驱动控制板。双路总功率 240W，单路最大功率 120W，支持绝大部分的云台电机FOC 位置、速度、力矩开闭环控制。编码器方面支持常见IIC和ABI、PWM制式。**加入在线电流检测模块，实现真正完整的FOC控制**。总的来说， 灯哥开源 FOC 控制器是一个好用又便宜的双路无刷FOC驱动器，点击查看 [效果视频](https://www.bilibili.com/video/BV1Hz4y127FL/)。

​     灯哥开源无刷FOC目前的发展受到灯哥开源团队的深度支持，目前已经针对这块控制板开发出了[灯哥开源无刷四足机器人](https://github.com/ToanTech/py-apple-bldc-quadruped-robot)，DIY视频和效果见：[B站](https://www.bilibili.com/video/BV1kV411i76z/)，后续还有无刷平衡车，倒立摆等等运行示例推出，敬请关注。

* **目前该主控板已经上架淘宝，是焊接好调试好的成品，出售即包括 ESP32** ；有需要大家可以猛击[淘宝链接（进店后在 所有宝贝 处可找到）](https://shop564514875.taobao.com/)

* 开源工作不易，希望大家多点 Star ,视频多一键三联！！！

![image1](pic/PAFOC_front_v3.jpg)

## 1 软件特性（支持 SimpleFOC库 2.2.2--最新库）

  作为国内最早引入 SimpleFOC 的团队，我们一直在致力深度改进 SimpleFOC硬件使其本土化，让大家能够以低廉的价格玩动无刷FOC算法。SimpleFOC是一个支持强大的开源库，可以实现无刷电机开闭环力矩、速度、位置控制，具体特性如下：

- **基于 Arduino**：运行在 ESP32 Arduino 上

- **开源**: 所有代码和配置文档都可以在：[SimpleFOC文档页](https://docs.simplefoc.com/) 找到

- **轻量化**：相比 Odrive 等驱动器，更加轻量化的软件结构可以帮你高速完成算法学习及配置

- **控制模式丰富**：开/闭环 速度、位置；以及开环的基于力矩控制；两种FOC内核算法

- **图形化配置软件**:最新的 DengFOC 对应支持使用 **SimpleFOC Studio** 进行电机参数配置，如下图所示，配置方法请见 文档PDF

  ![image1](pic/SimpleFOC_Studio.gif)

## 2 硬件特性

| 说明             | 参数                                                         |
| ---------------- | ------------------------------------------------------------ |
| 尺寸             | 56*39 mm                                                     |
| 输入电压类型     | 直流DC                                                       |
| 输入电压         | 12-24V                                                       |
| 最大功率         | 单路120W 双路共240W                                          |
| 支持电机数       | 2                                                            |
| 主控             | 底面搭载ESP32开发板 lolin32 lite                             |
| 编码器支持       | IIC方式、ABI方式、PWM方式编码器(AS5600、AS5047、AS5048等)、SPI方式、HALL编码器 |
| 拓展接口         | 串口（可以通过串口对FOC板子进行控制）                        |
| 电流检测参考电压 | 3.3V                                                         |
| 电流检测最大电流 | 3.3A                                                         |

## 3 重要链接

本 FOC 库与 DengFOC 硬件联合组成一整套完整可用的 FOC 电机驱动方案，资料链接：

1 [灯哥开源 淘宝店--一站配齐DengFOC板](https://shop564514875.taobao.com/) 您的支持就是我们持续做开源内容和课程的动力，项目收益将用于后续开发DengFOC和做课程~

2 [DengFOC库 Github](https://github.com/ToanTech/DengFOC_Lib)

3 [DengFOC官网](dengfoc.com) 包含课程文字版讲义，DengFOC使用文档，库使用方法等。

## 4 社区

本FOC板子社区唯三Q群，欢迎加入：**开源FOC无刷驱动交流群 灯哥开源 群号 778255240（1群） 735755513（2群）471832283（3群）**

任何使用问题和 DIY 问题 都会在这里做直接的讨论解答

## 5 项目文件说明

* Dengs FOC V3.0 DIY资料：BOM、原理图、PCB、Gerber
* Dengs FOC V3.0 测试例程：21个灯哥开源FOC开环、闭环、应用方面的测试视频
* 灯哥开源 FOC 使用文档 PDF：**配置的详细方式和使用教程**

## 6 DengFOC配套应用实践项目

利用DengFOC做的有趣的无刷电机实践项目：

[1 动量轮倒立摆项目，低成本化和小型化后应用在DengFOC上](https://github.com/ToanTech/Inverted_Pendulum_DengFOC)

[2 自平衡 DengFOC莱洛三角形](https://github.com/ToanTech/Lailuo_DengFOC)

[3 自平衡 DengFOC无刷平衡车](https://github.com/ToanTech/Balance_Bot_DengFOC)

[4 基于DengFOC的无刷四足并联腿机器狗](https://github.com/ToanTech/py-apple-bldc-quadruped-robot)

## 7 免费手把手教写FOC算法原理课

为了方便大家更进一步的理解FOC的算法和原理，我做了手把手教些FOC算法原理课，通过这些原理课你能够快速的从原理角度理解FOC知识并尝试写出自己的FOC基本功能库，视频链接：

1 [【手把手教写FOC算法】1_起源，无刷电机概念与控制原理](https://www.bilibili.com/video/BV1dy4y1X7yx)

2 [【手把手教写FOC算法】2_克拉克变换，建立简化电机数学模型](https://www.bilibili.com/video/BV1x84y1V76u/)

3 [【手把手教写FOC算法】3_等幅值变换与克拉克逆变换](https://www.bilibili.com/video/BV13s4y1Z7Tg/)

4 [【手把手教写FOC算法】4_帕克变换](https://www.bilibili.com/video/BV1t24y1u7do/)

5a [【手把手教写FOC算法】5a_撰写开环速度代码的前置知识](https://www.bilibili.com/video/BV1Pc411s7mP/)

5b [【手把手教写FOC算法】5b_开环速度代码编程+硬件调试教学](https://www.bilibili.com/video/BV16X4y167XZ/)

6a [【手把手教写FOC算法】6a_撰写闭环位置代码的前置知识](https://www.bilibili.com/video/BV1Rm4y1871K/)

6b [【手把手教写FOC算法】6b_闭环位置代码编程+硬件调试教学](https://www.bilibili.com/video/BV1yh4y1J7Xx/)
