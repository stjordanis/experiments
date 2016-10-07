#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  Wire.begin();
}

void loop() {
  selector(6);
  int16_t reading;
  Wire.beginTransmission(0x36);       // transmit to device as5601
  Wire.write(byte(0x0E));             // sets register pointer 
  Wire.endTransmission();    // stop transmitting
  //assume that we can always receiving the correct bytes
  Wire.requestFrom(0x36, 2);         // request 2 bytes from as5601
  reading = Wire.read();             // receive high byte 
  reading = reading << 8;            // shift high byte to be high 8 bits
  reading |= Wire.read();            // receive low byte as lower 8 bits
  Serial.println(reading);

  delay(100);
}
void selector(int i) {
  if (i>7) return;
  Wire.beginTransmission(0x70);
  Wire.write(1<<i);
  Wire.endTransmission();
}
