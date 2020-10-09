long duration;
float distance;
int counter=0;
float reading[] = {40, 40, 40, 40};

#define TRIG 6
#define ECHO 7

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT); 

  attachInterrupt(digitalPinToInterrupt(2), pulse, RISING); 
  attachInterrupt(digitalPinToInterrupt(3), cycle, RISING);
  
  Serial.begin(9600);
}

void pulse()          
{         
  counter++;          
  digitalWrite(6, LOW);
  delayMicroseconds(2);
  digitalWrite(6, HIGH);
  delayMicroseconds(10);
  digitalWrite(6, LOW);
  
  duration = pulseIn(7, HIGH, 20000);
  distance = duration * 0.034;

  if (distance < 100){
    reading[counter-1] = distance;
  }
  
  Serial.print(reading[counter-1]);
  Serial.print(" ");
}

void cycle(){
  counter = 0;
  Serial.println();
}

void loop() {


}
