long duration;
float distance;
int counter=0;
float reading[] = {40, 40, 40, 40};

#define TRIG 14 //D5
#define ECHO 12 //D6
//#define sync1 4 //D2
#define sync1 5 //D1


void setup() {
  Serial.begin(115200);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT); 

  attachInterrupt(digitalPinToInterrupt(sync1), get_distance, FALLING);
  //attachInterrupt(digitalPinToInterrupt(sync2), cycle, RISING);
 
}

ICACHE_RAM_ATTR void get_distance(){         
            
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, HIGH, 20000);
  distance = duration * 0.034;

  if (distance < 100){
    reading[counter] = distance;
  }
  
  Serial.print(reading[counter]);
  Serial.print(" ");

  counter++;
  if (counter == 4){
    Serial.println();
    counter = 0;
  }
}


ICACHE_RAM_ATTR void cycle(){
  counter = 0;
  Serial.println();
}

void loop() {


}
