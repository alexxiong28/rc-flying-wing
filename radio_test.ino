String x;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//import libraries 

const uint64_t pipeOut = 0xE9E8F0F0E1LL;  
int dataroll = 127;
int datapitch = 127;
RF24 radio(9, 10);

String serialData; //data sent from computer by python code

struct Signal{
  byte throttle; //controll throttle of plane
  byte right;    //right servo signal
  byte left;     //left servo signal
};
Signal data;

//signal range from 0-255 127 is middle point
void ResetData(){
  data.throttle = 12;
  data.left = 127;
  data.right = 127;
}


void setup() {
 Serial.begin(115200);
 Serial.setTimeout(1);
 radio.begin();
}

void loop() {
 while (!Serial.available());
 x = Serial.readString();
 Serial.print(x);
}
