# ⚡ IoT-Based Smart Energy Meter

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif" />
  <img src="https://img.shields.io/badge/IoT-Blynk-00C4CC?style=for-the-badge&logo=blynk" />
  <img src="https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge&logo=arduino" />
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus" />
</p>

<p align="center">
  <b>A real-time IoT-based energy monitoring system powered by ESP32.</b>
  <br />
  Monitor electrical parameters, track energy consumption, and calculate electricity costs through an interactive Blynk dashboard.
</p>

---

## 📌 Overview

An ESP32-based IoT energy monitoring system that measures real-time electrical parameters and streams them to the Blynk mobile dashboard.

The system integrates voltage and current sensors to monitor electrical consumption, calculates energy usage and estimated electricity costs, and displays live readings on a 16×2 I²C LCD.

Persistent storage ensures that accumulated energy consumption and cost data are retained even after power interruptions.

## ✨ Features

- Measures **Vrms**, **Irms**, **apparent power**, and **kWh** consumption.
- Calculates **electricity cost** based on a configurable rate per kWh.
- Displays live readings on a **16×2 I²C LCD** (alternates between two pages).
- Sends data to **Blynk** dashboard over WiFi every 2 seconds.
- Persists kWh and cost across power cycles using **EEPROM**.
- Hardware reset button to clear stored energy data.

## 🛠️ Hardware

| Component | Part | Pin |
|-----------|------|-----|
| MCU | ESP32 (38-pin dev board) | — |
| Voltage sensor | ZMPT101B | GPIO 35 (ADC) |
| Current sensor | ACS712 | GPIO 34 (ADC) |
| LCD | 16×2 I²C (0x27) | SDA=21, SCL=22 |
| Reset button | Tactile switch | GPIO 4 |

## 📸 Project Gallery

### Hardware Implementation

<p align="center">
  <img src="https://github.com/user-attachments/assets/2371ba31-737d-4637-a445-8e50b776d7ff" width="80%" alt="IoT Energy Meter Setup" />
</p>

### Monitoring Interface

<p align="center">
  <img src="https://github.com/user-attachments/assets/c68f2a0e-6794-49a4-9302-207e6a54af32" width="80%" alt="Screenshot" />
</p>

### Hardware Details

<p align="center">
  <img src="https://github.com/user-attachments/assets/6f9fe0d9-efe5-47ec-80df-4721842be644" width="80%" alt="IoT Energy Meter Hardware" />
</p>

## 🔌 Circuit Diagram

<p align="center">
  <img width="1122" height="622" alt="Circuit Diagram" src="https://github.com/user-attachments/assets/406d39ec-8597-4998-a5fe-21b2e4b6f6ac" />
</p>

## 📚 Libraries Required

The following libraries are required to compile and run the project:

- [EmonLib](https://github.com/openenergymonitor/EmonLib)
- [BlynkSimpleEsp32](https://github.com/blynkkk/blynk-library)
- LiquidCrystal_I2C
- Wire, EEPROM, WiFi (ESP32 built-in)

## 🚀 Setup & Installation

### 1. Configure Blynk

Create a Blynk template with 5 virtual pins:

| Virtual Pin | Data |
|-------------|------|
| V0 | Voltage (Vrms) |
| V1 | Current (Irms) |
| V2 | Power (W) |
| V3 | Energy (kWh) |
| V4 | Cost (₹) |

### 2. Configure Credentials

Copy your credentials into the sketch:

```cpp
const char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
const char ssid[] = "YOUR_WIFI_SSID";
const char pass[] = "YOUR_WIFI_PASSWORD";
```

### 3. Adjust Calibration Constants

Adjust the calibration values according to your sensors and electricity tariff:

```cpp
const float vCalibration    = 200;   // tune for your ZMPT101B
const float currCalibration = 0.25;  // tune for your ACS712
const float ratePerKwh      = 7;     // electricity rate in ₹/kWh
```

### 4. Upload to ESP32

Flash to ESP32 using Arduino IDE with the ESP32 board package installed.

## 📱 Blynk Dashboard (Virtual Pins)

The LCD cycles between two display pages every 2 seconds:

- **Page 0:** Voltage, Current, Power
- **Page 1:** Energy consumed (kWh), Cost (₹)

The Blynk dashboard receives the following parameters through virtual pins:

| Virtual Pin | Parameter | Unit |
|-------------|-----------|------|
| V0 | Voltage | V |
| V1 | Current | A |
| V2 | Power | W |
| V3 | Energy Consumption | kWh |
| V4 | Electricity Cost | ₹ |

---

## ⚙️ System Specifications

| Specification | Details |
|---------------|---------|
| Microcontroller | ESP32 |
| Voltage Measurement | ZMPT101B |
| Current Measurement | ACS712 |
| Local Display | 16×2 I²C LCD |
| Cloud Platform | Blynk IoT |
| Wireless Connectivity | WiFi |
| Data Persistence | EEPROM |
| Data Update Interval | 2 seconds |
| Programming Language | C++ |

---

<p align="center">
  <b>⚡ Smart Energy Monitoring | IoT | ESP32</b>
  <br />
  <i>Designed to make electricity monitoring smarter and more accessible.</i>
</p>
