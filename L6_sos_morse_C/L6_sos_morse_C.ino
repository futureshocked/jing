void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
}

void loop()
{  
  //This produces 3 short signals
  three_flashes(100);
    //This produces 3 long signals
  three_flashes(200);  
    //This produces 3 short signals
  three_flashes(100);
  
  delay(500);
}

void three_flashes(int duration)
{
   for(int i = 0; i < 3; i++)
  {
     Serial.print(".");
     digitalWrite(13, HIGH);
     delay(duration);
     digitalWrite(13, LOW);
     delay(duration); 
  }
}
