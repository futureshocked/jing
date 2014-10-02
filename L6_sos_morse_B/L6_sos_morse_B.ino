void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
}

void loop()
{  
  //This produces 3 short signals
  three_dots();
    //This produces 3 long signals
  three_dashes();  
    //This produces 3 short signals
  three_dots();
  
  delay(500);
}

void three_dots()
{
   for(int i = 0; i < 3; i++)
  {
     Serial.print(".");
     digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(13, LOW);
     delay(100);
  } 
}

void three_dashes()
{
  for(int i = 0; i < 3; i++)
  {
     Serial.print("_");
     digitalWrite(13, HIGH);
     delay(200);
     digitalWrite(13, LOW);
     delay(200);
  } 
}
