void setup()
{
  Serial.begin(9600);
  int a = 5;
  
  Serial.print("a=");
  Serial.println(a);
  
  Serial.print("5+5=");
  Serial.println(5+5);
  
  Serial.print("5-5=");
  Serial.println(5-5);
  
  Serial.print("5*5=");
  Serial.println(5*5);
  
  Serial.print("5/2=");
  Serial.println(5/2);
  
  Serial.print("5%2=");
  Serial.println(5%2);
  
  Serial.print("4==5 is ");
  Serial.println(4==5);
  
  Serial.print("4!=5 is ");
  Serial.println(4!=5);
  
  Serial.print("4>5 is ");
  Serial.println(4>5);
  
  Serial.print("4<5 is ");
  Serial.println(4<5);
  
  Serial.print("5<5 is ");
  Serial.println(5<5);
  
  Serial.print("4>=5 is ");
  Serial.println(4>=5);
  
  Serial.print("4<=5 is ");
  Serial.println(4<=5);
  
  Serial.print("5<=5 is ");
  Serial.println(5<=5);
}

void loop()
{}
