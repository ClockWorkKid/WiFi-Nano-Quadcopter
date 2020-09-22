void init_laser();
void update_laser();

void setup() {
  Serial.begin(115200);
  init_laser();
  IMUInit();
}

void loop() {
  update_laser();
  IMURead();
}
