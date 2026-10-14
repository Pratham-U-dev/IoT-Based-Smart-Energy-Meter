# IoT-Based Smart Energy Meter

An ESP32-based IoT energy monitoring system that measures real-time electrical parameters and streams them to the Blynk mobile dashboard.

## Features

- Measures **Vrms**, **Irms**, **apparent power**, and **kWh** consumption
- Calculates **electricity cost** based on a configurable rate per kWh
- Displays live readings on a **16×2 I²C LCD** (alternates between two pages)
- Sends data to **Blynk** dashboard over WiFi every 2 seconds
- Persists kWh and cost across power cycles using **EEPROM**
- Hardware reset button to clear stored energy data


## Pictures

<p align="center">
  <img src="https://github.com/user-attachments/assets/2371ba31-737d-4637-a445-8e50b776d7ff" width="80%" alt="IoT Energy Meter Setup" />
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/c68f2a0e-6794-49a4-9302-207e6a54af32" width="80%" alt="Screenshot" />
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/6f9fe0d9-efe5-47ec-80df-4721842be644" width="80%" alt="IoT Energy Meter Hardware" />
</p>

## Circuit Diagram

<img width="1122" height="622" alt="image" src="https://github.com/user-attachments/assets/406d39ec-8597-4998-a5fe-21b2e4b6f6ac" />


## Hardware

| Component | Part | Pin |
|-----------|------|-----|
| MCU | ESP32 (38-pin dev board) | — |
| Voltage sensor | ZMPT101B | GPIO 35 (ADC) |
| Current sensor | ACS712 | GPIO 34 (ADC) |
| LCD | 16×2 I²C (0x27) | SDA=21, SCL=22 |
| Reset button | Tactile switch | GPIO 4 |

## Libraries Required

- [EmonLib](https://github.com/openenergymonitor/EmonLib)
- [BlynkSimpleEsp32](https://github.com/blynkkk/blynk-library)
- LiquidCrystal_I2C
- Wire, EEPROM, WiFi (ESP32 built-in)

## Setup

1. Create a Blynk template with 5 virtual pins:

| Virtual Pin | Data |
|-------------|------|
| V0 | Voltage (Vrms) |
| V1 | Current (Irms) |
| V2 | Power (W) |
| V3 | Energy (kWh) |
| V4 | Cost (₹) |

2. Copy your credentials into the sketch:

```cpp
const char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
const char ssid[] = "YOUR_WIFI_SSID";
const char pass[] = "YOUR_WIFI_PASSWORD";
```

3. Adjust calibration constants if needed:

```cpp
const float vCalibration    = 200;   // tune for your ZMPT101B
const float currCalibration = 0.25;  // tune for your ACS712
const float ratePerKwh      = 7;     // electricity rate in ₹/kWh
```

4. Flash to ESP32 using Arduino IDE with the ESP32 board package installed.

## Blynk Dashboard (Virtual Pins)

The LCD cycles between two display pages every 2 seconds:
- **Page 0:** Voltage, Current, Power
- **Page 1:** Energy consumed (kWh), Cost (₹)
