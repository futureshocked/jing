#include <SPI.h>
#include <LiquidCrystal.h>
#include "DHT.h"
#include "Wire.h"
#include "Adafruit_BMP085.h"
#include <Ethernet.h>
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 9, 5, 4, 3, 2);
Adafruit_BMP085 bmp;
float humidity = 0;
float temperature = 0;
float altitude = 0;
float pressure = 0;
int photoSensorPin = 1;
volatile int photoSensorValue = 0;
byte mac[] = { 0xDE, 0xAD, 0x45, 0xEF, 0xFE, 0xED };
byte ip[] = {192,168,111,177 };             
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 60000; 
const String APIKEY="4078c823691aeda32c3816206d5da8f3";          
const char URL[] ="emoncms.org";
const int PORT=80;
EthernetClient webClient;
 
void setup()
{
  Serial.begin(9600);       
  Serial.println("Starting.");
  Ethernet.begin(mac,ip);  
  Serial.println("up and running....");  
  bmp.begin(); 
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Starting up.");  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.setCursor(0,1);
  lcd.print("Started.");  
}
 
void loop()
{   
    delay(100);
    do_weblog();
}

// =========================================================================
/*
This is where it all happens.
If the posting interval is reached then a new POST is done with the latest data
If not time yet, we simply exit
 */
void do_weblog() {
    makeMeasurement();    
    if(!webClient.connected() && (millis() - lastConnectionTime > postingInterval)) {
        Serial.println("Transmitting.");
        sendData();
    }
}

void makeMeasurement()
{
  pressure = bmp.readPressure() / 100;
  altitude = bmp.readAltitude();     
  photoSensorValue = analogRead(photoSensorPin);  //get the voltage value from input pin
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
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

void sendData() {
    // Create the 'content' string to send. 
    String json;
    json =  "{temp:";
    json +=  String(temperature);
    json += ",hum:";
    json += String(humidity);
    json += ",pres:";
    json += String(pressure);
    json += ",alt:";
    json += String(altitude);
    json += ",lum:";
    json += String(photoSensorValue);
    json +=  "}";
    String str;        
    str = "GET ";
    str += "/input/post.json?json=";
    str +=  json;
    str += "&apikey=";
    str +=  APIKEY;
    str += " HTTP/1.1\r\n";
    str += "Host: ";
    str += URL;
    str += "\r\n";
    str += "User-Agent: Arduino-ethernet\r\n";
    str += "Connection: close\r\n";
    str += "\r\n";        
    Serial.println();              
    Serial.print(str);     
    Serial.println();
    Serial.println();
    Serial.println("connecting...");
    if (webClient.connect(URL, PORT))
    {         
        webClient.print(str);  // send data to Emoncms
        delay(1000);        // wait for a response
        while (webClient.available()) {
          char c = webClient.read();
          Serial.print(c);
        }
    }

    else {
        // if you couldn't make a connection:
        Serial.println();
        Serial.println("Connection failed");
        Serial.println("disconnecting.");
        Serial.println();
        webClient.stop();
    }
    // note the time that the connection was made
    lastConnectionTime = millis();
}
