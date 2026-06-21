#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MAX30105.h>
#include "spo2_algorithm.h"
char ssid[] = " ";
char pass[] = " ";
LiquidCrystal_I2C lcd(0x27,16,2);
MAX30105 particleSensor;
#define BUFFER_SIZE 25
uint32_t irBuffer[BUFFER_SIZE];
uint32_t redBuffer[BUFFER_SIZE];
int sampleIndex = 0;
int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;
float tempC;
int touchState;
const int tempPin = 34;
const int touchPin = 4;
const int greenLED = 16;
const int redLED = 17;
const int buzzer = 19;
BlynkTimer timer;
unsigned long lastLCD = 0;
void sendToBlynk() {
  Blynk.virtualWrite(V0, tempC);
  if(validHeartRate && validSPO2){
    Blynk.virtualWrite(V1, heartRate);
    Blynk.virtualWrite(V2, spo2);
  }
}
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Health Monitor");
  lcd.setCursor(0,1);
  lcd.print("System Ready");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(touchPin, INPUT);
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    lcd.setCursor(0,0);
    lcd.print("MAX ERROR");
    while (1);
  }
  particleSensor.setup(60, 4, 2, 100, 411, 4096);
  for(int i=0;i<BUFFER_SIZE;i++){
    while(!particleSensor.available()) particleSensor.check();
    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample();
  }
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sendToBlynk);
}
void loop() {
  long irValue = particleSensor.getIR();
  bool fingerPresent = (irValue > 50000);
  if(fingerPresent && particleSensor.available()){
    redBuffer[sampleIndex] = particleSensor.getRed();
    irBuffer[sampleIndex] = particleSensor.getIR();
    particleSensor.nextSample();
    sampleIndex++;
    if(sampleIndex >= BUFFER_SIZE){
      maxim_heart_rate_and_oxygen_saturation(
        irBuffer, BUFFER_SIZE,
        redBuffer,
        &spo2, &validSPO2,
        &heartRate, &validHeartRate
      );
      sampleIndex = 0;
    }
  }
  float sum = 0;
  for(int i=0;i<5;i++){
    sum += analogRead(tempPin);
  }
  tempC = (sum/5.0) * (3.3/4095.0) * 100.0;
  touchState = digitalRead(touchPin);
  if(touchState){
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
  digitalWrite(buzzer, touchState ? HIGH : LOW);
  if(millis() - lastLCD > 1000){
    lastLCD = millis();
    lcd.setCursor(0,0);
    if(!fingerPresent){
      lcd.print("Place Finger   ");
      lcd.setCursor(0,1);
      lcd.print("                ");
    } else {
      lcd.print("T:");
      lcd.print(tempC,1);
      lcd.print((char)223);
      lcd.print("C ");
      lcd.print("HR:");
      if(validHeartRate){
        lcd.print(heartRate);
        lcd.print("   ");
      } else {
        lcd.print("--   ");
      }
      lcd.setCursor(0,1);
      lcd.print("SpO2:");
      if(validSPO2){
        lcd.print(spo2);
        lcd.print("% ");
      } else {
        lcd.print("-- ");
      }
      lcd.print(touchState ? "ON " : "OFF");
    }
  }
  Serial.print("Touch: ");
  Serial.println(touchState);
  Blynk.run();
  timer.run();
}
