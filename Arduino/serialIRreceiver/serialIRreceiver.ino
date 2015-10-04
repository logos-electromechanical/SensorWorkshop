
void setup() {
  //Serial.begin(9600); 
  Serial.begin(2400); 
}
 
void loop() {
  // send data only when you receive data:
      if (Serial.available() > 0) {
              // read the incoming byte:
              char incomingByte = Serial.read();

              // say what you got:
              Serial.print(incomingByte);
      }
}
