#include <EmonLib.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "IoT Energy Meter"
#define BLYNK_PRINT Serial

LiquidCrystal_I2C lcd(0x27, 16, 2);

const float vCalibration    = 200;
const float currCalibration = 0.25;

const char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
const char ssid[] = "YOUR_WIFI_SSID";
const char pass[] = "YOUR_WIFI_PASSWORD";

EnergyMonitor emon;
BlynkTimer timer;

float kWh  = 0.0;
float cost = 0.0;

const float       ratePerKwh    = 7;
unsigned long     lastMillis    = millis();
const int         addrKwh       = 12;
const int         addrCost      = 16;
int               displayPage   = 0;
const int         resetButtonPin = 4;

void sendEnergyDataToBlynk();
void readEnergyDataFromEEPROM();
void saveEnergyDataToEEPROM();
void updateLCD();
void changeDisplayPage();
void resetEEPROM();

// ──────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Blynk.begin(auth, ssid, pass);
  lcd.init();
  lcd.backlight();
  EEPROM.begin(32);
  pinMode(resetButtonPin, INPUT_PULLUP);
  emon.voltage(35, vCalibration, 0);
  emon.current(34, currCalibration);
  timer.setInterval(2000L, sendEnergyDataToBlynk);
  timer.setInterval(2000L, changeDisplayPage);
  Serial.println("Setup complete");
}

void loop() {
  Blynk.run();
  timer.run();
  if (digitalRead(resetButtonPin) == LOW) {
    delay(200);
    if (digitalRead(resetButtonPin) == LOW) {
      resetEEPROM();
    }
  }
}

// ──────────────────────────────────────────────
void sendEnergyDataToBlynk() {
  emon.calcVI(20, 2000);
  float Vrms = emon.Vrms;
  float Irms = emon.Irms;

  if (!isnan(Vrms) && !isnan(Irms)) {
    if (Vrms < 20.0) { Vrms = 0; }
    if (Irms < 0.3)  { Irms = 0; }

    unsigned long currentMillis = millis();
    kWh  += emon.apparentPower * (currentMillis - lastMillis) / 3600000000.0;
    lastMillis = currentMillis;
    cost = kWh * ratePerKwh;

    saveEnergyDataToEEPROM();

    Blynk.virtualWrite(V0, Vrms);
    Blynk.virtualWrite(V1, Irms);
    Blynk.virtualWrite(V2, emon.apparentPower);
    Blynk.virtualWrite(V3, kWh);
    Blynk.virtualWrite(V4, cost);

    updateLCD();
  } else {
    Serial.println("Invalid voltage/current readings");
  }
}

void readEnergyDataFromEEPROM() {
  EEPROM.get(addrKwh, kWh);
  EEPROM.get(addrCost, cost);
  if (isnan(kWh)) {
    kWh = 0.0;
    saveEnergyDataToEEPROM();
  }
  if (isnan(cost)) {
    cost = 0.0;
    saveEnergyDataToEEPROM();
  }
}

void saveEnergyDataToEEPROM() {
  EEPROM.put(addrKwh, kWh);
  EEPROM.put(addrCost, cost);
  EEPROM.commit();
}

void updateLCD() {
  lcd.clear();
  if (displayPage == 0) {
    lcd.setCursor(0, 0);
    lcd.printf("V:%.1fV I: %.2fA", emon.Vrms, emon.Irms);
    lcd.setCursor(0, 1);
    lcd.printf("P: %.1fW", emon.apparentPower);
  } else if (displayPage == 1) {
    lcd.setCursor(0, 0);
    lcd.printf("Energy: %.2fkWh", kWh);
    lcd.setCursor(0, 1);
    lcd.printf("Cost: %.2f", cost);
  }
}

void changeDisplayPage() {
  displayPage = (displayPage + 1) % 2;
  updateLCD();
}

void resetEEPROM() {
  kWh  = 0.0;
  cost = 0.0;
  saveEnergyDataToEEPROM();
}
