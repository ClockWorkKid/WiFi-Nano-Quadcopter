volatile unsigned long elapsed=0;
hw_timer_t *timer = NULL;

void IRAM_ATTR ppmISR() {
  static boolean state = 0;
  static uint8_t curr_chan = 0;
  uint16_t timer_write = 0;

  if (!state) {           // If pulse was low, start new pulse
    if (curr_chan >= CHANNEL_NUMBER) {    // If all channels iterated, reset channel counter, calculate time left to FRAME_LENGTH
      timer_write = FRAME_LENGTH + PULSE_LENGTH - elapsed;
      elapsed = 0;
      curr_chan = 0;
    }
    else {            // If all channels not iterated, calculate next pulse
      ppm[curr_chan] = constrain(ppm[curr_chan], 1000, 2000);
      timer_write = FRAME_LENGTH + PULSE_LENGTH - ppm[curr_chan];
      elapsed += ppm[curr_chan];
      curr_chan += 1;
    }
  }
  else {
    timer_write = FRAME_LENGTH - PULSE_LENGTH;
  }

  state = !state;
  digitalWrite(sigPin, !state);
  timerWrite(timer, timer_write);

}

void ppm_begin(void) {
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, 0); //set the PPM signal pin to the default state (off)

  noInterrupts();
  timer = timerBegin(0, 80, true);              //timer 0, div 80
  timerAttachInterrupt(timer, &ppmISR, true);  //attach callback
  timerAlarmWrite(timer, FRAME_LENGTH, true); //set time in us
  timerAlarmEnable(timer);                     //enable interrupt
  for (int i = 0; i < CHANNEL_NUMBER; i++) {
    ppm[i] = CHANNEL_DEFAULT_VALUE;
  }
  interrupts();
}
