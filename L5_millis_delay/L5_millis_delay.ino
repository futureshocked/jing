
unsigned long time;
void setup(){
   Serial.begin(9600);
}
void loop(){
   Serial.print("Time: ");
   time = millis();
   Serial.println(time);
   delay(1000);
}

