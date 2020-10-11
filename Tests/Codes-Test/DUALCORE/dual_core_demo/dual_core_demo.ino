TaskHandle_t CORE0;
TaskHandle_t CORE1;

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    main_0,   /* Task function. */
    "main_0",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &CORE0,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
  delay(500);

  xTaskCreatePinnedToCore(
    main_1,   /* Task function. */
    "main_1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &CORE1,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */
  delay(500);
}

void loop(){
  
}
void setup_0();
void setup_1();
void loop_0();
void loop_1();

void main_0( void * pvParameters ) {
  setup_0();
  while (true)loop_0();
}

void main_1( void * pvParameters ) {
  setup_1();
  while (true)loop_1();
}
