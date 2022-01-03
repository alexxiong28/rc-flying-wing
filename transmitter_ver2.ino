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
  radio.begin();
  Serial.begin(115200);
  Serial.setTimeout(1);
  radio.openWritingPipe(pipeOut);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
  ResetData(); //set all to initial position
}

void loop() {
  while(!Serial.available());
  serialData = Serial.readString();
    //Serial.print(serialData);
  int throttleval = parseThrottle(serialData);
  int pitchval = parsePitch(serialData);
  int rollval = parseRoll(serialData);
    
  radio.write(&data, sizeof(Signal));
  Serial.println(serialData);
  

}


//data is the the structure: TxxxPxxxRxxx
//containing throtttle, pitch and roll data
int parseThrottle(String data){
  data.remove(data.indexOf("P"));
  data.remove(data.indexOf("T"),1);

  return data.toInt();
}

int parsePitch(String data){
  data.remove(data.indexOf("R"));
  data.remove(0, data.indexOf("P")+1);

  return data.toInt();
  
}

int parseRoll(String data){
  data.remove(0, data.indexOf("R")+1);

  return data.toInt();
}
