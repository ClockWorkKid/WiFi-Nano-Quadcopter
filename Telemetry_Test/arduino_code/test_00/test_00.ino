#define range 800
#define pin1 11
#define pin2 12
int arr_1[range];

void setup() {
  pinMode(pin1, INPUT);
  Serial.begin(57600);
  Serial.println("Beginning");
}

void loop() {
 
  for(int i = 0; i < range; i++){
    arr_1[i] = digitalRead(pin1);

  }
   for(int i = 0; i < range; i++){
    Serial.println(arr_1[i]);
  }

}
