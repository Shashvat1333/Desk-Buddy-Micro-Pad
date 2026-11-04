# Desk-Buddy-Micro-Pad

A desk buddy that reacts to you throught a touch sensor and allows you to play a single play ping pong game or set a timer for yourself. On top of that it also has a building micro pad where you can auto mate three thing on your device from a single click. 

<img width="1062" height="770" alt="image" src="https://github.com/user-attachments/assets/a3ec0c0d-f38d-4688-8b42-9186237718a5" />

## Table of Contents
- [What It Does](#what-it-does)
- [CAD Model](#cad-model)
- [Wiring](#wiring)
- [Firmware](#firmware)
- [Getting Started](#getting-started)
- [Bill of Materials (BOM)](#bill-of-materials-bom)
- [License](#license)

## What It Does

- **1 touch pads:** Touch the pad on the top of the desk buddy to react with it.
- **2 emotions:** Make it happy for 3 secounds by taping the pad once or made by taping it 3+ times.
- **Set a timer or play a game** Tap it exactly twice to set a timer or hold for 3 secounds to play a ping pong game using a potentiometer.
- **Automate something on your device:** Make something you use everyday easy using the 3 keys.

---

## CAD Model

Enclosure designed in Onshape: [View Onshape Model](https://cad.onshape.com/documents/63adeef6886e48c42ac3f940/w/7a23baff083423aa6f7d1430/e/b7cafec5227014a420d5a64e?renderMode=0&uiState=6ae7f9126a47f3d1b920d4d5)

[Step Files are here](https://github.com/Shashvat1333/Desk-Buddy-Micro-Pad/tree/main/CAD)

---

## Wiring

- **Schematic:** [Piano Sampler.kicad_sch](https://github.com/Shashvat1333/Desk-Buddy-Micro-Pad/blob/main/Desk%20Buddy.kicad_sch)
- **Full wiring:** [Wiring Diagram.md](https://github.com/Shashvat1333/Desk-Buddy-Micro-Pad/blob/main/Wiring%20Diagram.md)

<img width="660" height="432" alt="image" src="https://github.com/user-attachments/assets/01564203-a563-4db2-8575-985d9e465918" />

---

## Firmware

- **Code:** [FIRMWARE.ino](https://github.com/Shashvat1333/Desk-Buddy-Micro-Pad/blob/main/Firmware.ino)
- **Libraries:** `Wire.h`, ` Adafruit_GFX.h`, `Adafruit_SSD1306.h`, `USB.h`, `USBHIDKeyboard.h`
- **Board:** ESP32-S3 Mini

---

## Getting Started

2. **Assemble the hardware:** Print and assembly the body, mount the components, and solder the connections using the wiring table.
3. **Upload the code:** Open `FIRMWARE.ino` in the Arduino IDE, install the libraries, select **ESP32-S3 Dev Module**, and upload.
4. **Power and have fun:** Plug the ESP32 into you computer for power and to automate something on you computer.

---

## Bill of Materials (BOM)

| Item | Qty | Supplier | Cost/item | Total Cost | Link |
|------|-----|----------|-----------|------------|------|
| Kailh BOX White V2 | 1 | AliExpress | $4.84 | $4.84 | [Link](https://www.aliexpress.com/item/1005003957173643.html) |
| ESP32-S3 | 1 | AliExpress | $7.63 | $7.63| [Link](https://www.aliexpress.com/item/1005007524137218.html) |
| Touch Button Module | 1 | AliExpress | $3.85 | $3.85 | [Link](https://www.aliexpress.com/item/1005006246380749.html) |
| 0.96 Inch OLED Display Module SSD1306 I2C | 1 | AliExpress | $3.9 | $3.9 | [Link](https://www.aliexpress.com/item/1005004355547926.html) |
| 10k Potentiometer | 1 | AliExpress | $3.40 | $3.40 | [Link](https://www.aliexpress.com/item/4001274951434.html) |
| **Total** | | | | **$23.62 CAD** | |

---

## License

This project is licensed under the terms in [LICENSE.md](https://github.com/Shashvat1333/Desk-Buddy-Micro-Pad/blob/main/LICENSE.md).
