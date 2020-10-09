//#include <SoftwareSerial.h>
//
//#define cr_pin 9
//
//SoftwareSerial IRSerial(11, 12);
//
//void setup() {
//  IRSerial.begin(1200);  /* Define baud rate for serial communication */
//  tone(cr_pin, 38000);  /* For modulation at 38kHz */
//}
//
//void loop() {
//  int count;
//  for (count = 0; count < 9; count++)
//  {
//    IRSerial.println(count);
//    delay(1000);
//  }
//}
