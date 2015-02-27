#include "Wire.h"
#include <SPI.h>
#include <LiquidCrystal.h>
#include "DHT.h"
#include "Adafruit_BMP085.h"

#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Adafruit_BMP085 bmp;

float humidity = 0;
float temperature = 0;
float altitude = 0;
float pressure = 0;

int photoSensorPin = 1;
volatile int photoSensorValue = 0;
 
void setup()
{
   Serial.begin(9600);     
   bmp.begin(); 
   dht.begin();
   lcd.begin(16, 2);
   lcd.print("Starting up.");
   lcd.setCursor(0,0);  
}
 
void loop()
{   
   delay(100);
   makeMeasurement();
}

void makeMeasurement()
{
   pressure = bmp.readPressure() / 100;
   altitude = bmp.readAltitude();     
   photoSensorValue = analogRead(photoSensorPin); 
   humidity = dht.readHumidity();
   temperature = dht.readTemperature();
   Serial.println(humidity);  
   lcd.clear();
   lcd.print("H:");
   lcd.print(humidity);
   lcd.print("%");
   lcd.print("A:");
   lcd.print(altitude);
   lcd.setCursor(0, 1);
   lcd.print("T:");
   lcd.print(temperature);
   lcd.print("C");
   lcd.print(",L:");
   lcd.print(photoSensorValue);
   lcd.print("U"); 
}
