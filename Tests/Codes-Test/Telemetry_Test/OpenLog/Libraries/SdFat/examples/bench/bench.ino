/*
 * This program is a simple binary write/read benchmark.
 */
#include <SPI.h>
#include <SdFat.h>
#include <FreeStack.h>

// SD chip select pin
const uint8_t chipSelect = SS;

// Size of read/write.
const size_t BUF_SIZE = 512;

// File size in MB where MB = 1,000,000 bytes.
const uint32_t FILE_SIZE_MB = 5;

// Write pass count.
const uint8_t WRITE_COUNT = 10;

// Read pass count.
const uint8_t READ_COUNT = 5;
//==============================================================================
// End of configuration constants.
//------------------------------------------------------------------------------
// File size in bytes.
const uint32_t FILE_SIZE = 1000000UL*FILE_SIZE_MB;

uint8_t buf[BUF_SIZE];

// file system
SdFat sd;

// test file
SdFile file;

// Serial output stream
ArduinoOutStream cout(Serial);
//------------------------------------------------------------------------------
// store error strings in flash to save RAM
#define error(s) sd.errorHalt(F(s))
//------------------------------------------------------------------------------
void cidDmp() {
  cid_t cid;
  if (!sd.card()->readCID(&cid)) {
    error("readCID failed");
  }
  cout << F("\nManufacturer ID: ");
  cout << hex << int(cid.mid) << dec << endl;
  cout << F("OEM ID: ") << cid.oid[0] << cid.oid[1] << endl;
  cout << F("Product: ");
  for (uint8_t i = 0; i < 5; i++) {
    cout << cid.pnm[i];
  }
  cout << F("\nVersion: ");
  cout << int(cid.prv_n) << '.' << int(cid.prv_m) << endl;
  cout << F("Serial number: ") << hex << cid.psn << dec << endl;
  cout << F("Manufacturing date: ");
  cout << int(cid.mdt_month) << '/';
  cout << (2000 + cid.mdt_year_low + 10 * cid.mdt_year_high) << endl;
  cout << endl;
}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  while (!Serial) {} // wait for Leonardo
  delay(1000);
  cout << F("\nUse a freshly formatted SD for best performance.\n");

  // use uppercase in hex and use 0X base prefix
  cout << uppercase << showbase << endl;
}
//------------------------------------------------------------------------------
void loop() {
  float s;
  uint32_t t;
  uint32_t maxLatency;
  uint32_t minLatency;
  uint32_t totalLatency;

  // discard any input
  while (Serial.read() >= 0) {}

  // F( stores strings in flash to save RAM
  cout << F("Type any character to start\n");
  while (Serial.read() <= 0) {}
  delay(400);  // catch Due reset problem

  cout << F("FreeStack: ") << FreeStack() << endl;

  // initialize the SD card at SPI_FULL_SPEED for best performance.
  // try SPI_HALF_SPEED if bus errors occur.
  if (!sd.begin(chipSelect, SPI_FULL_SPEED)) {
    sd.initErrorHalt();
  }

  cout << F("Type is FAT") << int(sd.vol()->fatType()) << endl;
  cout << F("Card size: ") << sd.card()->cardSize()*512E-9;
  cout << F(" GB (GB = 1E9 bytes)") << endl;

  cidDmp();

  // open or create file - truncate existing file.
  if (!file.open("bench.dat", O_CREAT | O_TRUNC | O_RDWR)) {
    error("open failed");
  }

  // fill buf with known data
  for (uint16_t i = 0; i < (BUF_SIZE-2); i++) {
    buf[i] = 'A' + (i % 26);
  }
  buf[BUF_SIZE-2] = '\r';
  buf[BUF_SIZE-1] = '\n';

  cout << F("File size ") << FILE_SIZE_MB << F(" MB\n");
  cout << F("Buffer size ") << BUF_SIZE << F(" bytes\n");
  cout << F("Starting write test, please wait.") << endl << endl;

  // do write test
  uint32_t n = FILE_SIZE/sizeof(buf);
  cout <<F("write speed and latency") << endl;
  cout << F("speed,max,min,avg") << endl;
  cout << F("KB/Sec,usec,usec,usec") << endl;
  for (uint8_t nTest = 0; nTest < WRITE_COUNT; nTest++) {
    file.truncate(0);
    maxLatency = 0;
    minLatency = 9999999;
    totalLatency = 0;
    t = millis();
    for (uint32_t i = 0; i < n; i++) {
      uint32_t m = micros();
      if (file.write(buf, sizeof(buf)) != sizeof(buf)) {
        error("write failed");
      }
      m = micros() - m;
      if (maxLatency < m) {
        maxLatency = m;
      }
      if (minLatency > m) {
        minLatency = m;
      }
      totalLatency += m;
    }
    file.sync();
    t = millis() - t;
    s = file.fileSize();
    cout << s/t <<',' << maxLatency << ',' << minLatency;
    cout << ',' << totalLatency/n << endl;
  }

  cout << endl << F("Starting read test, please wait.") << endl;
  cout << endl <<F("read speed and latency") << endl;
  cout << F("speed,max,min,avg") << endl;
  cout << F("KB/Sec,usec,usec,usec") << endl;
  // do read test
  for (uint8_t nTest = 0; nTest < READ_COUNT; nTest++) {
    file.rewind();
    maxLatency = 0;
    minLatency = 9999999;
    totalLatency = 0;
    t = millis();
    for (uint32_t i = 0; i < n; i++) {
      buf[BUF_SIZE-1] = 0;
      uint32_t m = micros();
      if (file.read(buf, sizeof(buf)) != sizeof(buf)) {
        error("read failed");
      }
      m = micros() - m;
      if (maxLatency < m) {
        maxLatency = m;
      }
      if (minLatency > m) {
        minLatency = m;
      }
      totalLatency += m;
      if (buf[BUF_SIZE-1] != '\n') {
        error("data check");
      }
    }
    t = millis() - t;
    cout << s/t <<',' << maxLatency << ',' << minLatency;
    cout << ',' << totalLatency/n << endl;
  }
  cout << endl << F("Done") << endl;
  file.close();
}