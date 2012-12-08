#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#define ONE_WIRE_BUS 2


Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix1 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix();

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

DeviceAddress temp0;

boolean toggle =0;

void setup(void){
  Serial.begin(9600);
  sensors.begin();
  matrix.begin(0x72);
  matrix1.begin(0x71);
  matrix2.begin(0x70);
  if (!sensors.getAddress(temp0, 0)) Serial.println("Unable to find address for temp0"); 
  sensors.setResolution(temp0, 12);
  pinMode(7,OUTPUT);
}

void printTemperature(DeviceAddress deviceAddress){
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.println(tempC);
}

void print(float p){
  
  matrix1.clear();
  matrix1.setTextSize(0.5);
  matrix1.setTextWrap(false);
  matrix1.setTextColor(LED_ON);
  matrix1.setCursor(0,0);
  matrix1.print(p);
  matrix1.writeDisplay();

  matrix.clear();
  matrix.setTextSize(0.5);
  matrix.setTextWrap(false);
  matrix.setTextColor(LED_ON);
  matrix.setCursor(-8,0);
  matrix.print(p);
  matrix.writeDisplay();

  matrix2.clear();
  matrix2.setTextSize(0.5);
  matrix2.setTextWrap(false);
  matrix2.setTextColor(LED_ON);
  matrix2.setCursor(-16,0);
  matrix2.print(p);
  matrix2.writeDisplay();
}

void loop(void){
  sensors.requestTemperatures();
  printTemperature(temp0);
  int value = analogRead(A0);
  float c = (value/50.0F) + 50;
  Serial.println(c);
  float r = sensors.getTempC(temp0);
  print(toggle ? r:c);
  toggle = !toggle;
  if (r < c) {
    digitalWrite(7, HIGH);
  }else{
    digitalWrite(7, LOW);
  }
}

