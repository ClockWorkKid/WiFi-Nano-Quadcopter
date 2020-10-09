void setup() {
  for (int i = 0; i< 4; i++)
    pinMode(i+2, OUTPUT); 

  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
}

void loop() {
  for (int i = 0; i< 4; i++){
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(i+2, LOW); 
    
    delayMicroseconds(2);
    
    digitalWrite(12, LOW);
    digitalWrite(i+2, HIGH);
    
    delayMicroseconds(10);
    digitalWrite(i+2, LOW);
    
    delay(25);
  }
  
  digitalWrite(13, LOW);
  delay(25);
}
