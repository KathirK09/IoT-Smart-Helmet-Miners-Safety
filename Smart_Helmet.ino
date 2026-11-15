/*
  IoT-Based Smart Helmet for Miners' Safety — starter firmware

  Proposed example wiring (VERIFY your actual hardware):
    MQ-135 AO -> A0
    DHT11 DATA -> D2
    I2C LCD SDA -> A4, SCL -> A5 (Arduino Uno)
    Green LED -> D9 through a current-limiting resistor
    Red LED   -> D8 through a current-limiting resistor

  Libraries:
    - Adafruit DHT sensor library
    - Adafruit Unified Sensor
    - A compatible LiquidCrystal_I2C library

  SAFETY:
    MQ-135 raw ADC values are NOT ppm and are NOT a certified gas alarm.
    The threshold below is a placeholder for bench demonstration only.
    This project is not certified safety equipment.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ---------- Verify/change these settings for your actual circuit ----------
const byte MQ135_PIN = A0;
const byte DHT_PIN = 2;
const byte GREEN_LED_PIN = 9;
const byte RED_LED_PIN = 8;

#define DHT_TYPE DHT11

// Common I2C addresses are 0x27 or 0x3F. Confirm with an I2C scanner.
const byte LCD_ADDRESS = 0x27;

// DEMONSTRATION PLACEHOLDER ONLY — not a gas concentration or safety limit.
// Determine a suitable experimental value only through documented testing.
const int MQ135_DEMO_THRESHOLD = 400;
// -------------------------------------------------------------------------

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL_MS = 2000;

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  Serial.begin(9600);
  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Helmet");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(1500);
  lcd.clear();

  Serial.println(F("Smart Helmet prototype started."));
  Serial.println(F("MQ-135 values are raw ADC readings, not ppm."));
}

void loop() {
  if (millis() - lastReadTime < READ_INTERVAL_MS) {
    return;
  }
  lastReadTime = millis();

  int mqRaw = analogRead(MQ135_PIN);
  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();

  Serial.print(F("MQ135 raw ADC: "));
  Serial.println(mqRaw);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas raw:");
  lcd.print(mqRaw);

  if (isnan(humidity) || isnan(temperatureC)) {
    lcd.setCursor(0, 1);
    lcd.print("DHT read error");
    Serial.println(F("DHT11 read failed. Check wiring and sensor."));
  } else {
    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(temperatureC, 1);
    lcd.print("C H:");
    lcd.print(humidity, 0);
    lcd.print("%");

    Serial.print(F("Temperature C: "));
    Serial.println(temperatureC, 1);
    Serial.print(F("Humidity %: "));
    Serial.println(humidity, 0);
  }

  // Demonstration LED logic only; threshold is not a certified alarm limit.
  if (mqRaw >= MQ135_DEMO_THRESHOLD) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    Serial.println(F("LED status: RED (demo threshold reached)"));
  } else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    Serial.println(F("LED status: GREEN (below demo threshold)"));
  }

  Serial.println(F("------------------------------"));
}
