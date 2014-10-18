void setup() {
  Serial.begin(115200); 
}

void loop() {
  Serial.print(analogRead(0));
  Serial.print("\t");
  Serial.println(analogRead(1));
}
