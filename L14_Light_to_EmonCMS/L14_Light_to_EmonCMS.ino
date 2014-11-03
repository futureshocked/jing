#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
IPAddress ip(192,168,111, 177);
IPAddress gateway(192,168,111, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetClient webClient;

unsigned long lastConnectionTime = 0;         
const unsigned long postingInterval = 60000;                                                

const String APIKEY="4078c823691aeda32c3816206d5da8f3";          
const char URL[] ="emoncms.org";
const int PORT=80;

int photoSensorPin = 1;
volatile int photoSensorValue = 0;

void setup() {
  Serial.begin(9600);     
  Serial.println("Starting.");
  Ethernet.begin(mac,ip);  
  Serial.println("up and running....");
}

void loop() { 
    delay(5000);
    do_weblog();
}

void do_weblog() {
    makeMeasurement();    
    if(!webClient.connected() && (millis() - lastConnectionTime > postingInterval)) {
        Serial.println("Transmitting.");
        sendData();
    }
}

void makeMeasurement()
{   
  photoSensorValue = analogRead(photoSensorPin);
}

void sendData() {
    String json;
    json =  "{lum:";
    json += String(photoSensorValue);
    json +=  "}";
    Serial.println("connecting...");
    if (webClient.connect(URL, PORT))     // make the attempt...
    { 
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
        webClient.print(str); 
        Serial.println();     
        Serial.print(str);    
        Serial.println();     
        Serial.println();     

        delay(1000);   // wait a bit for a response
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
    lastConnectionTime = millis();
}
