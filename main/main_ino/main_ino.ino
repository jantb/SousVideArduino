#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

DeviceAddress temp0;
DeviceAddress temp1;

void setup(void){
  Serial.begin(9600);

  sensors.begin();
  if (!sensors.getAddress(temp0, 0)) Serial.println("Unable to find address for temp0"); 
  if (!sensors.getAddress(temp1, 1)) Serial.println("Unable to find address for temp1"); 
  sensors.setResolution(temp0, 12);
  sensors.setResolution(temp1, 12);
}

void printTemperature(DeviceAddress deviceAddress){
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.println(tempC);
}

void loop(void){ 
  sensors.requestTemperatures();
  printTemperature(temp0);
  printTemperature(temp1);
  int value = analogRead(A0);
  float c = (value/50.0F) + 50;
  Serial.println(c);
}

