void setup()
{
  Serial.begin(9600);
  
  Serial.println("This is an if...else test");
  int someVariable = 40;
  Serial.print("The test variable is ");
  Serial.print(someVariable);
  if (someVariable > 50)
  {
    Serial.println(". It's larger than 50!");
  }
  else
  {
    Serial.println(". It's not larger than 50!");
  }

  Serial.println();
  Serial.println("This is a for test");
  for (int i=0; i <= 5; i++){
     Serial.println(i);
   }
  
  Serial.println();
  Serial.println("This is a while test");
  someVariable = 0;
  while(someVariable <= 5){
    Serial.println(someVariable);
    someVariable++;
  }
}

void loop()
{}
