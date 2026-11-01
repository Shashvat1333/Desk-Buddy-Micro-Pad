**Desk Buddy + Micro Pad Wiring Diagram**
------------------------------------------------------------------------

<img width="660" height="432" alt="image" src="https://github.com/user-attachments/assets/3b39aa91-59f8-4448-b3f6-281e8c704c3c" />

------------------------------------------------------------------------

| Component | ESP32 Pin | Module / Component Pin | Wire Connection |
| :--- | :--- | :--- | :--- |
| **I2C OLED** | GND | GND | GND - GND |
| **I2C OLED** | 3V3 | VCC | 3V3 - VCC |
| **I2C OLED** | GPIO 7 | SDA | GPIO 7 - SDA |
| **I2C OLED** | GPIO 8 | SCL | GPIO 8 - SCL |
| **TTP1 Touch** | GND | GND | GND - GND |
| **TTP1 Touch** | 3V3 | VCC | 3V3 - VCC |
| **TTP1 Touch** | GPIO 3 | I/O | GPIO 3 - I/O |
| **Mechanical Switches** | GND | Common Ground Leg | GND - GND (First leg all switches) |
| **Mechanical Switches** | GPIO 5 | Button 1 | GPIO 5 - Button 1 |
| **Mechanical Switches** | GPIO 6 | Button 2 | GPIO 6 - Button 2 |
| **Mechanical Switches** | GPIO 9 | Button 3 | GPIO 9 - Button 3 |
| **10K Potentiometer** | 3V3 | Leg 1 | 3V3 - Leg 1 |
| **10K Potentiometer** | GPIO 4 | Leg 2 (Wiper) | GPIO 4 - Leg 2 |
| **10K Potentiometer** | GND | Leg 3 | GND - Leg 3 |

------------------------------------------------------------------------
