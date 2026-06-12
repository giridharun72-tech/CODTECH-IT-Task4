# TASK 4: CONTACTLESS AUTOMATIC SANITIZER DISPENSER

## 👤 Intern Information
* **Intern ID:** CITS4432
* **Full Name:** GIRIDHARUN S
* **Domain:** Internet of Things (IoT)
* **Duration:** 4 Weeks

---

## 📌 Project Overview
This project presents an intermediate-level architectural layout for an automated touchless sanitization station engineered for the ESP32 platform. Built as a hardware-in-the-loop software model, the system tracks real-time distance proximity using acoustic ultrasonic ping transceivers and processes metrics via localized boundary loops to execute timed liquid dispensing cycles automatically.

This design emphasizes baseline sanitization hygiene compliance and system interlocks to prevent mechanical fluid flooding.

---
This link for my simulation in it wokwi.com for the task automatic sanitizer dispenser working link:https://wokwi.com/projects/466595755163935745

## 🏗️ System Architecture
The touchless control state-machine flows as detailed below:

```text
[ HC-SR04 Echo Node ] ──(GPIO 5/18)──> [ ESP32 MCU ] ──(Digital GPIO 23)──> [ Submersible Pump LED ]
                                            │
                                            └──(UART Terminal)──> [ Proximity Log Telemetry ]
