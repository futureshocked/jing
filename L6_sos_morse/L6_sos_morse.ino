void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
}

void loop()
{  
  //This produces 3 short signals
   for(int i = 0; i < 3; i++)
  {
    Serial.print(".");
     digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(13, LOW);
     delay(100);
  } 
  
    //This produces 3 long signals
   for(int i = 0; i < 3; i++)
  {
        Serial.print("_");
     digitalWrite(13, HIGH);
     delay(200);
     digitalWrite(13, LOW);
     delay(200);
  } 
  
    //This produces 3 short signals
   for(int i = 0; i < 3; i++)
  {
    Serial.print(".");
     digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(13, LOW);
     delay(100);
  } 
  
  Serial.println();
  delay(500);
}
