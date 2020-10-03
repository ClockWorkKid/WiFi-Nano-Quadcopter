// FrSky "D8" transmitter module telemetry decode
// by ceptimus on 2015-09-10

uint8_t rssi;
uint8_t a1;
uint8_t a2;
int16_t timeout;

char* format(uint8_t low, uint8_t high) { // format the 16-bit integer formed by high:low in ASCII decimal.  Negative values have a leading '-' values < 10 have one leading '0'
  static char buffer[8];
  char *p;
  p = buffer;
  int16_t i = (int16_t)high;
  i = (i << 8) | low;
  if (i < 0) {
    *p++ = '-';
    i = -i;
  }
  if (i < 9) {
    *p++ = '0';
  }
  for (int16_t tenPower = i > 9999 ? 10000 : i > 999 ? 1000 : i > 99 ? 100 : i > 9 ? 10 : 1; tenPower > 0; tenPower /= 10) {
    uint8_t digit = '0';
    while (i >= tenPower) {
      digit++;
      i -= tenPower;
    }
    *p++ = digit;
  }
  *p = '\0';
  return buffer;
}

void handleDataByte(uint8_t data) {
  static uint8_t dataPacket[4];
  static uint8_t FrSkyUserDataMode = 0;
  static uint8_t FrSkyUserDataLow;
  static uint8_t FrSkyTelemetryDataID;
  static bool FrSkyUserDataStuffing;
  static bool FrSkyUserDataLowFlag; // flag for low byte of data, which is the first of the following two
  int16_t i;
  uint8_t high, low;

  switch (FrSkyUserDataMode) {
    case 0: // idle
      if (data == 0x5E) { // telemetry hub frames begin with ^ (0x5E)
        FrSkyUserDataMode = 1; // expect telemetry hub DataID next
      }
      break;
    case 1: // expecting telemetry hub DataID
      if (data < 0x3C) { // store DataID (address)
        FrSkyUserDataStuffing = false;
        FrSkyTelemetryDataID = data;
        FrSkyUserDataMode = 2; // expect two bytes of data next
        FrSkyUserDataLowFlag = true; // flag for low byte of data, which is the first of the following two
      }
      else if (data != 0x5E) { // the header byte 0x5E may occur twice running as it is also used as an 'end of frame' so remain in mode 1. Otherwise DataID was > 0x3B, so invalid
        FrSkyUserDataMode = 0; // back to idle mode
      }
      break;
    case 2: // expecting two bytes of data
      if (FrSkyUserDataStuffing) {
        FrSkyUserDataStuffing = false;
        if ((data != 0x3D) && (data != 0x3E)) { // byte stuffing is only valid for (unstuffed) bytes 0x5D or or 0x5E
          FrSkyUserDataMode = 0; // back to idle mode
          break;
        }
        else {
          data ^= 0x20; // unstuff byte
        }
      }
      else if (data == 0x5D) { // following byte is stuffed
        FrSkyUserDataStuffing = true;
        break;
      }
      if (FrSkyUserDataLowFlag) { // expecting low byte of data
        FrSkyUserDataLow = data; // remember low byte
        FrSkyUserDataLowFlag = false; // expect high byte next
      }
      else { // expecting high byte of data
        switch (FrSkyTelemetryDataID) {
          case 0x01: // 1st part of GPS altitude
          case 0x10: // 1st part of barimetric altitude
          case 0x11: // 1st part of GPS speed
          case 0x12: // 1st part of longitude
          case 0x13: // 1st part of latitude
          case 0x14: // 1st part of GPS course over ground
          case 0x15: // 1st part of date
          case 0x17: // 1st part of time
            dataPacket[0] = FrSkyUserDataLow;
            dataPacket[1] = data; // store value till last part received
            break;
          case 0x02: // temperature 1
            Serial.print("Temperature 1: ");
            Serial.print(format(FrSkyUserDataLow, data));
            Serial.print("\n");
            break;
          case 0x05: // temperature 2
            Serial.print("Temperature 2: ");
            Serial.print(format(FrSkyUserDataLow, data));
            Serial.print("\n");
            break;
          case 0x09: // second (final) part of GPS altitude
            Serial.print("GPS Altitude: ");
            Serial.print(format(dataPacket[0], dataPacket[1]));
            Serial.print(".");
            Serial.print(format(FrSkyUserDataLow, data));
            Serial.print("\n");
            break;
          case 0x16: // second (final) part of date
            Serial.print("Date: 20"); // assume 21st century
            Serial.print(format(FrSkyUserDataLow, 0)); // year
            Serial.print("-");
            Serial.print(format(dataPacket[1], 0)); // month
            Serial.print("-");
            Serial.print(format(dataPacket[0], 0)); // day
            Serial.print("\n");
            break;
          case 0x18: // second (final) part of time
            Serial.print("Time: ");
            Serial.print(format(dataPacket[0], 0)); // hour
            Serial.print(":");
            Serial.print(format(dataPacket[1], 0)); // minute
            Serial.print(":");
            Serial.print(format(FrSkyUserDataLow, 0)); // second
            Serial.print("\n");
            break;
          case 0x19: // second (final) part of GPS speed
            Serial.print("GPS speed: ");
            Serial.print(format(dataPacket[0], dataPacket[1]));
            Serial.print(".");
            Serial.print(format(FrSkyUserDataLow, data));
            Serial.print("\n");
            break;
          case 0x1A: // second part of longitude
          case 0x1B: // second part of latitude
            dataPacket[2] = FrSkyUserDataLow;
            dataPacket[3] = data; // store value till last part received
            break;
          case 0x1C: // second (final) part of GPS cog
            Serial.print("GPS C.O.G.: ");
            Serial.print(format(dataPacket[0], dataPacket[1]));
            Serial.print(".");
            Serial.print(format(FrSkyUserDataLow, data));
            Serial.print("\n");
            break;
          case 0x21: // second (final) part of barometric altitude
            Serial.print("Barometric Altitude: ");
            Serial.print(format(dataPacket[0], dataPacket[1]));
            Serial.print(".");
            Serial.print(format(FrSkyUserDataLow, data));
            Serial.print("\n");
            break;
          case 0x22: // third (final) part of longitude
            Serial.print("Longitude: ");
            i = (uint16_t)dataPacket[1];
            i = (i << 8) | dataPacket[0]; // degrees * 100 + minutes
            high = (i / 100) >> 8; low = (i / 100) & 0x00FF;
            Serial.print(format(low, high));
            Serial.print(" deg ");
            Serial.print(format(i % 100, 0));
            Serial.print(".");
            Serial.print(format(dataPacket[2], dataPacket[3]));
            Serial.print(" min ");
            Serial.write(FrSkyUserDataLow); // 'E' or 'W'
            Serial.print("\n");
            break;
          case 0x23: // third (final) part of latitude
            Serial.print("Latitude: ");
            i = (uint16_t)dataPacket[1];
            i = (i << 8) | dataPacket[0]; // degrees * 100 + minutes
            high = (i / 100) >> 8; low = (i / 100) & 0x00FF;
            Serial.print(format(low, high));
            Serial.print(" deg ");
            Serial.print(format(i % 100, 0));
            Serial.print(".");
            Serial.print(format(dataPacket[2], dataPacket[3]));
            Serial.print(" min ");
            Serial.write(FrSkyUserDataLow); // 'N' or 'S'
            Serial.print("\n");
            break;
          case 0x24: // x acceleration
            Serial.print("X acceleration: ");
            Serial.print(format(FrSkyUserDataLow, data));
            Serial.print("\n");
            break;
          case 0x25: // y acceleration
            Serial.print("Y acceleration: ");
            Serial.print(format(FrSkyUserDataLow, data));
            Serial.print("\n");
            break;
          case 0x26: // z acceleration
            Serial.print("Z acceleration: ");
            Serial.print(format(FrSkyUserDataLow, data));
            Serial.print("\n");
            break;
          default:
            break;
        }
        FrSkyUserDataMode = 0; // received and stored both data bytes, so back to idle mode
      } // else
      break;
    default: // should never happen
      FrSkyUserDataMode = 0; // back to idle mode
      break;
  }
}

void handlePacket(uint8_t *packet) {
  switch (packet[0]) {
    case 0xFD:
      if (packet[1] > 0 && packet[1] <= 6) {
        for (int i = 0; i < packet[1]; i++) {
          handleDataByte(packet[3 + i]);
        }
      }
      cli(); timeout = 1000; sei();
      break;
    case 0xFE:
      a1 = packet[1]; // A1:
      a2 = packet[2]; // A2:
      rssi = packet[3]; // main (Rx) link quality 100+ is full signal  40 is no signal
      // packet[4] secondary (Tx) link quality.  Strength of signal received by Tx so not particularly useful.  Numbers are about double those of RSSI.
      cli(); timeout = 1000; sei();
      break;
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
    if (rssi) {
      Serial.println("No telemetry data being received");
    } else {
      Serial.print("RSSI: ");
      Serial.print(rssi);
      Serial.print(" AD1: ");
      Serial.print(a1);
      Serial.print(" AD2: ");
      Serial.print(a2);
      Serial.print('\n');
    }
    millisTillNextPrint += 500 - ms;
  } else {
    millisTillNextPrint -= ms;
  }
}
