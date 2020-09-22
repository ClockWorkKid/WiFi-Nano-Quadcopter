#define LED_pin 2
#define READ_pin 27
#define threshold 2000

void init_laser() {
  pinMode(LED_pin,OUTPUT);
  digitalWrite(LED_pin,0);
}

void update_laser() {
  int a = analogRead(READ_pin);
  //Serial.println(a);
  if(a > threshold)
    digitalWrite(LED_pin,HIGH);
  else
    digitalWrite(LED_pin,LOW);
}
