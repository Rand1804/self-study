# 数字电路

## 数制和码制

### 数制

我们把多位数码中每一位的构成方法以及从低位到高位的进位规则称为数制

1. 基数：所用到的数字符号的个数
2. 位权：用来表明不同数位上数值大小的一个固定常数

### 码制

仅用于标识区分，不作为大小或计算用

## 逻辑代数基础

### 与

![image-20240124211904587](assets/image-20240124211904587.png)

逻辑乘

Y=A.B = AB

与门

![image-20240124211631595](assets/image-20240124211631595.png)

### 或

![image-20240124211950211](assets/image-20240124211950211.png)

逻辑加

Y = A + B

或门

![image-20240124212211930](assets/image-20240124212211930.png)

### 非

Y = A' 或 Y = A^_

![image-20240124212526808](assets/image-20240124212526808.png)

![image-20240124212825711](assets/image-20240124212825711.png)

![image-20240124212855259](assets/image-20240124212855259.png)

### 组合逻辑运算

![image-20240124214159359](assets/image-20240124214159359.png)

![image-20240124214617149](assets/image-20240124214617149.png)

### 公式

![image-20240124220201851](assets/image-20240124220201851.png)

![image-20240124220223947](assets/image-20240124220223947.png)

### 定理

![image-20240124221903080](assets/image-20240124221903080.png)

![image-20240124221917691](assets/image-20240124221917691.png)

![image-20240124221932242](assets/image-20240124221932242.png)

![image-20240124222140036](assets/image-20240124222140036.png)

### 逻辑函数的表达方式

![image-20240124223238279](assets/image-20240124223238279.png)

#### 相互转换

##### 真值表转换逻辑函数式

1. 首先找到所有值为1的项
2. 输入值为0则取反，为1则不变，然后与上
3. 最后将所有输入项或上

![image-20240124225802550](assets/image-20240124225802550.png)

##### 逻辑函数转为真值表

代入所有可能的值并计算出结果即可

##### 逻辑运算转为逻辑图（画电路图）

依次画出逻辑门并连接即可

##### 逻辑图转为逻辑运算（分析电路图）

![image-20240124230431309](assets/image-20240124230431309.png)

### 最小项

![image-20240124232431155](assets/image-20240124232431155.png)

![image-20240124232451488](assets/image-20240124232451488.png)

##### 最小项性质

![image-20240124232713036](assets/image-20240124232713036.png)

### 最大项

![image-20240124233154022](assets/image-20240124233154022.png)

![image-20240125012236809](assets/image-20240125012236809.png)

![image-20240125012606375](assets/image-20240125012606375.png)

## 门电路

![image-20240125020627983](assets/image-20240125020627983.png)

### 二极管与门

![image-20240125023515815](assets/image-20240125023515815.png)

### 二极管或门

![image-20240125024139570](assets/image-20240125024139570.png)

二极管无法实现非门

![image-20240125044810735](assets/image-20240125044810735.png)

![image-20240125225305512](assets/image-20240125225305512.png)

![image-20240125230150264](assets/image-20240125230150264.png)

源极表示传统电流流出的端子

![image-20240125231633963](assets/image-20240125231633963.png)

![image-20240125231702929](assets/image-20240125231702929.png)

在二极管中，p型材料和n型材料是两种不同类型的半导体材料，它们共同构成二极管的核心。

1. **P型材料（P-type Material）**：这种材料是通过在纯净的硅或锗等半导体中掺杂少量的三价元素（如硼、镓）制成的。这种掺杂方式会在半导体中产生“空穴”，即电子缺失的位置，从而使材料带有正电。在p型材料中，空穴充当主要的载流子。

2. **N型材料（N-type Material）**：这种材料是通过在纯净的硅或锗等半导体中掺杂少量的五价元素（如磷、砷）制成的。这种掺杂方式会在半导体中额外产生自由电子，从而使材料带有负电。在n型材料中，自由电子充当主要的载流子。

当p型和n型材料结合在一起时，它们的接触界面形成了所谓的“PN结”，这是二极管的关键部分。在PN结处，自由电子和空穴相结合，形成一个阻止电流轻易通过的“耗尽区”。当适当的电压施加在二极管上时，耗尽区可以被消除，允许电流流过，从而使二极管导通。这种特性使得二极管在电路中扮演关键角色，如整流和信号控制等功能。

![image-20240126030802121](assets/image-20240126030802121.png)

![image-20240126030857104](assets/image-20240126030857104.png)

**NPN**: 电流从集电极和基极进入，汇总后发射极流出。基极比发射极高0.7V才能导通

**PNP**: 电流从发射极进入，从集电极和基极流出

Emitter	Base	Collector

![image-20240126031247576](assets/image-20240126031247576.png)

![image-20240126031421063](assets/image-20240126031421063.png)

![image-20240126031453209](assets/image-20240126031453209.png)

![image-20240126034454110](assets/image-20240126034454110.png)

![image-20240126034746124](assets/image-20240126034746124.png)

![image-20240126035111461](assets/image-20240126035111461.png)





## 附录

### 概念

#### Power

1. **POWER_EN (Power Enable)**:

- This is often a control signal or pin used to enable or disable power to a particular part of a circuit.
- In microcontroller-based systems, it could be a digital output from the MCU used to control a power regulator, a power MOSFET, or another type of power switch.
- The purpose of a POWER_EN signal is usually to manage power consumption by turning off certain circuit sections when they are not needed.

2. **ACC_DET (Accessory Detect)**:

- This term is commonly used in automotive electronics, but can also be found in other types of devices.
- In the context of vehicles, "ACC" stands for "Accessory", and ACC_DET could be a signal or input pin used to detect when the vehicle's accessory systems are active (e.g., radio, lights, etc.).
- It can also be a feature in mobile devices or other electronics to detect the connection of accessories like headphones, chargers, etc.

3. **BAT_ADC (Battery ADC)**:

- "BAT_ADC" typically refers to a Battery Analog-to-Digital Converter.
- This is usually a part of a circuit used to monitor battery voltage or current. The ADC (Analog-to-Digital Converter) converts the analog voltage or current level from the battery into a digital value that a microcontroller can process.
- This is crucial for battery management systems (BMS) in devices like smartphones, laptops, or electric vehicles, where it's important to accurately monitor battery levels for efficient charging, power management, and protecting the battery from conditions like overcharging or deep discharge.

4. **MCU_3V3**

This usually refers to a 3.3 Volt power supply line that is used to power a microcontroller unit (MCU). The "3V3" indicates the voltage level, which is 3.3 volts. This is a common voltage level for modern MCUs and digital circuits.

5. **VDD**

This is a conventional designation for the positive power supply voltage in a circuit. In digital electronics, VDD refers to the voltage at which the digital ICs or components operate. The actual voltage level designated by VDD can vary based on the specifications of the integrated circuit or system. For example, it could be 5V, 3.3V, 1.8V, etc.

6. **VDDA**

This stands for "Analog Positive Power Supply Voltage". It is similar to VDD but specifically refers to the power supply for the analog sections of a circuit. In mixed-signal integrated circuits, which contain both analog and digital components, VDDA would supply the analog components, ensuring that they have a stable and noise-free power source. This is particularly important for precision analog components like analog-to-digital converters (ADCs) or digital-to-analog converters (DACs).

7. **VSS**

This is the common designation for the ground or negative terminal of a power supply in a circuit. In many digital systems, VSS is effectively the reference point against which all other voltages are measured. It's important in the context of both digital and analog circuits, serving as a return path for current.

8. MCU_5V

- **5 Volt Supply for Microcontroller**: The MCU_5V line would be the main power supply to the microcontroller. Many MCUs are designed to operate at 5 volts, although newer designs may operate at lower voltages like 3.3V or even lower for power efficiency.
- **Compatibility with Peripherals and Sensors**: A 5V power supply is often used because many peripheral devices, sensors, and other integrated circuits are also designed to operate at this voltage. This makes system integration easier, as all components are using a common voltage level.

9. VREFH

**VREFH** stands for "Voltage Reference High" and is a term commonly used in the context of electronic circuits, particularly in those involving analog-to-digital converters (ADCs) or digital-to-analog converters (DACs). 

10. **VCC**:

- Historically, "VCC" stood for "Voltage at the Collector of the Common" in bipolar junction transistors (BJTs), but in modern usage, it generally refers to the positive supply voltage for a circuit or a part of a circuit.
- In digital electronics, VCC is often the primary operating voltage for integrated circuits (ICs), microcontrollers, and digital systems. The actual voltage level for VCC can vary depending on the requirements of the system, common values being 5V, 3.3V, etc.

11. **VIO (Voltage for Input/Output)**:

- VIO refers to the voltage level used for the Input/Output (I/O) pins of a microcontroller or integrated circuit.
- This is particularly important in systems where the core of the IC operates at a different voltage than the I/O pins. For example, a microcontroller might run its processor core at a lower voltage for power efficiency, while the I/O pins operate at a higher voltage for compatibility with other components in the system.
- Providing a separate VIO allows for flexibility in interfacing with peripherals that might operate at different voltage levels.

12. **VBAT (Battery Voltage)**:

- VBAT typically refers to the voltage supplied by a battery.
- In the context of electronic devices, VBAT is used to denote the direct power line from a battery, which might be used to power the device when no external power source is available.
- VBAT is particularly relevant in circuits with battery management, where the battery voltage might need to be monitored for charging, power management, or to provide power to certain parts of the circuit during power outages or when unplugged from a main power source.

#### CAN

1. **CAN0_STB (CAN0 Standby)**:
    - This is typically a control signal used to put the CAN transceiver into a low-power standby mode.
    - In standby mode, the transceiver might maintain the ability to monitor the bus for activity and wake up the system if necessary, while consuming less power.

2. **CAN0_EN (CAN0 Enable)**:
    - This signal is used to enable or disable the CAN transceiver.
    - When enabled, the transceiver actively participates in CAN communication. When disabled, it disconnects from the CAN bus, effectively silencing the node.

3. **CAN0_ERR_N (CAN0 Error Negative)**:
    - This is usually an error indication signal.
    - It's often active-low (hence the "_N" suffix, indicating negative logic), meaning it is in a low state under error conditions.
    - The signal can be used by the system to detect error conditions on the CAN bus, like transmission errors, and take appropriate action.

4. **CAN0_TXD (CAN0 Transmit Data)**:
    - This is the data transmission line for the CAN bus.
    - It's used by the CAN controller to send data frames onto the CAN network.

5. **CAN0_RXD (CAN0 Receive Data)**:
    - This line is used for receiving data from the CAN bus.
    - The CAN controller uses this line to listen to data frames transmitted by other nodes on the network.

#### 箭头

The symbols "<<" and ">>" in electronic schematics like the one you've uploaded typically indicate the direction of signal flow or the directionality of a connection. These symbols can help in understanding how data is transferred or how control signals are issued within a circuit, especially in complex schematics involving microcontrollers or other integrated circuits. Here's what they generally mean:

- **"<<" (Double Left Arrow)**: This often indicates an input to a module or a part of the circuit. It suggests that this pin or line is meant to receive a signal from another part of the circuit.

- **">>" (Double Right Arrow)**: Conversely, this usually indicates an output from a module or a part of the circuit. It suggests that this pin or line is meant to send a signal to another part of the circuit.

- **"<< >>" (Double Left and Right Arrow)**: This can indicate that the signal is bidirectional or that the pin can both send and receive signals, depending on the context.

In the context of your image, which appears to be a pinout diagram for a microcontroller or a similar device, these symbols are likely being used to quickly convey the general purpose of each pin (whether it's primarily for input, output, or both) to someone reading the schematic.
