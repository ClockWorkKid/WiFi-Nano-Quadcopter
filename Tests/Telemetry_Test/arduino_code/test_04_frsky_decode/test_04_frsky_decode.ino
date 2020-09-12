// FrSky "D8" transmitter module telemetry decode
// by ceptimus on 2015-09-10

uint8_t rssi;
uint8_t a1;
uint8_t a2;
int16_t timeout;

void handlePacket(uint8_t *packet) {
  if (packet[0] == 0xFE) { // not interested in telemetry data other than the most basic kind for this application
    a1 = packet[1]; // A1: VCC (Rx voltage) volts = packet[1] * 5.17647E-2; constant is 3.3 * 4 / 255
    a2 = packet[2]; // A2: (usually scaled LiPo voltage)
    rssi = packet[3]; // main (Rx) link quality 100+ is full signal  40 is no signal
    // packet[4] secondary (Tx) link quality.  Strength of signal received by Tx so not particularly useful.  Numbers are about double those of RSSI.
    cli(); timeout = 1000; sei();
  }
}

void handleRxChar(uint8_t b) { // decode FrSky basic telemetry data
  static uint8_t packetPosition = 0;
  static uint8_t packet[9];
  static bool byteStuffing = false;

  if (b == 0x7E) { // framing character
    if (packetPosition == 9) {
      handlePacket(packet);
    }
    packetPosition = 0;
    return;
  }

  if (b == 0x7D) {
    byteStuffing = true;
    return;
  }

  if (byteStuffing) {
    byteStuffing = false;
    if (b != 0x5E && b != 0x5D) {
      packetPosition = 0;
      return;
    }
    b ^= 0x20;
  }

  if (packetPosition > 8) {
    packetPosition = 0;
  }
  else {
    packet[packetPosition++] = b;
  }
}

// this interrupt handler decodes incoming FrSky serial telemetry data on digital 11
// FrSky module gives out RS232 levels (like +/- 6V) so use 100K inline resistor and rely on ATMega input diode clamps to convert to TTL
// See Atmel application note AVR182 explaining how this is an approved way to do it (they even run mains voltage into a pin via a 1M resistor!)
// Signal is also inverted but this code flips the bits back the right way
// only works at 9600N81 with TCNT0 incrementing every 4 uS (e.g. ATmega328 @ 16 MHz)
// works without delay for character values < 128 so fine for normal ASCII
// when receiving character values > 127, the character isn't processed till the start bit of the following character is received
// so if frame ends with such a character, the frame won't be processed till the beginning of the next frame

ISR(PCINT0_vect) { // Port B pinchange interrupt
  static uint8_t prev = 0;
  static uint8_t currChar = 0;
  static uint8_t currBits = 0;
  uint8_t now = TCNT0;
  sei(); // allow other interrupts once time has been captured
  uint8_t bits = (((uint8_t)(now - prev)) + 13) / 26; // at 9600 baud with 4 uS TCNT, one bit is 1E6 / (4 * 9600) = 26.04 counts, so half a bit is ~13 counts
  if (!bits || bits > 9) { // detect 0 bits when gap between characters and TCNT0 wrapped exactly, also limit bits to 9 to prevent overflow of (currBits + bits)
    bits = 9;
  }
  prev = now;
  if (!(PINB & 0x08)) { // -ve edge, but inverted RS232 so preceding data bits were low
    if (!currBits) { // start of char so bits includes the start bit (start bit is low)
      currBits = 1; // currBits count does includes the start bit
      bits--; // but don't include start bit in character decode
    }
    currChar >>= bits; // received low bits represent '0' in character.  LSB arrives first, MSB last
    currBits += bits;
  }
  else if (currBits) { // preceding data bits were high
    if (currBits + bits > 9) { // trim stop bit if receiving character values >= 128 (MSB will be high and stop bit is also high)
      bits = 9 - currBits;
    }
    currChar = (0xFF00 | currChar) >> bits; // received high bits represent '1' in character.  LSB arrives first, MSB last
    currBits += bits;
  }
  if (currBits > 8) { // start bit plus character received
    uint8_t rxChar = currChar; // don't know if interrupt is re-entrant - if not then this won't help but if it is then allows next bit(s) to be received while handling char
    currChar = currBits = 0;
    handleRxChar(rxChar);
  }
}


uint32_t oldMillis;
int16_t millisTillNextPrint = 500; // send data to serial port twice per second

void setup(void) {
  pinMode(11, INPUT); // serial input (Digital 11 is Port B, bit 3)
  PCMSK0 = 0x08; // set mask to allow (only) digital pin 9 pinchange interrupts on Port B
  PCICR |= 0x01; // allow pinchange interrupts for Port B
  rssi = a1 = a2 = 0;
  timeout = 1000; // ms
  Serial.begin(57600);
  oldMillis = millis();
}

void loop(void) {
  uint32_t now = millis();
  int32_t ms = now - oldMillis; // milliseconds elapsed since last loop
  oldMillis = now;
  
  if (timeout <= (int16_t)ms) {
    timeout = a1 = a2 = rssi = 0;
  } else {
    timeout -= ms;
  }

  if (ms >= millisTillNextPrint) { // time to print
    if (!rssi) {
      Serial.println("No telemetry data being received");
    } else {
      Serial.print("RSSI: ");
      Serial.print(rssi);
      Serial.print(" AD1: ");
      Serial.print(a1);
      Serial.print(" AD2: ");
      Serial.println(a2);
    }
    millisTillNextPrint += 500 - ms;
  } else {
    millisTillNextPrint -= ms;
  }
}
