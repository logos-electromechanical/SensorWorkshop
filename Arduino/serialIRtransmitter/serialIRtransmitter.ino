

void setup()
{
  Serial.begin(2400);
}

void loop()
{
  tone(10,38000);
  Serial.println("Hello");
  delay(100); 
}
