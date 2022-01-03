// 6 Channel Transmitter | 6 Kanal Verici
  #include <SPI.h>
  #include <nRF24L01.h>
  #include <RF24.h>
  const uint64_t pipeOut = 0xE9E8F0F0E1LL;   //IMPORTANT: The same as in the receiver 0xE9E8F0F0E1LL | Bu adres alıcı ile aynı olmalı
  int dataroll = 127;
  int datapitch = 127;
  RF24 radio(9, 10); // select CE,CSN pin | CE ve CSN pinlerin seçimi
  struct Signal {
  byte throttle;
  byte right;
  byte left;
  byte yaw;
  byte aux1;
  byte aux2;

};
  Signal data;
  void ResetData() 
{
  data.throttle = 12;   // Motor stop | Motor Kapalı (Signal lost position | sinyal kesildiğindeki pozisyon)
  data.left = 127;    // Center | Merkez (Signal lost position | sinyal kesildiğindeki pozisyon)
  data.right = 127;     // Center | merkez (Signal lost position | sinyal kesildiğindeki pozisyon)
     // Center | merkez (Signal lost position | sinyal kesildiğindeki pozisyon)
}
  void setup()
{
  //Start everything up
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(pipeOut);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening(); //start the radio comunication for Transmitter | Verici olarak sinyal iletişimi başlatılıyor
  ResetData();
 
}
  // Joystick center and its borders | Joystick merkez ve sınırları
  int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
  val = map(val, lower, middle, 0, 128);
  else
  val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}
  void loop()
{
  // Control Stick Calibration | Kumanda Kol Kalibrasyonları
  // Setting may be required for the correct values of the control levers. | :Kontrol kolların doğru değerleri için ayar gerekebilir.


  int throttleval = constrain(analogRead(A0),151,609);
  int pitchval = constrain(analogRead(A1),143,509);
  int rollval = constrain(analogRead(A2), 112, 455);
  data.throttle = mapJoystickValues( throttleval, 150, 205, 610, true);  // "true" or "false" for signal direction | "true" veya "false" sinyal yönünü belirler
  //dataroll = mapJoystickValues( analogRead(A2), 112, 206, 430, true );      // "true" or "false" for servo direction | "true" veya "false" servo yönünü belirler
  datapitch = mapJoystickValues( pitchval, 142, 204, 510, true );     // "true" or "false" for servo direction | "true" veya "false" servo yönünü belirler

  if(rollval<170){
    dataroll = map(rollval, 112, 180, 0,127);
    }
  if(rollval>230){
    dataroll = map(rollval, 230,455, 127,255);
    //Serial.print("trigger");
  }
  if(rollval>170 && 230>rollval){
    dataroll = 127;
  }
  
  //if((analogRead(A1)>230)&&(analogRead(A1)<190)){
    //data.left = datapitch;
    //data.right = map(datapitch,0,255,255,0);
  //}
  
  data.left = constrain(datapitch-127+dataroll,0,255);
  data.right = constrain(datapitch+127-dataroll, 0,255);
  radio.write(&data, sizeof(Signal));

  Serial.print("throttle: ");
  Serial.print(data.throttle);
  Serial.print(" pitch: ");
  Serial.print(analogRead(A1));
  Serial.print(" roll: ");
  Serial.print(analogRead(A2));
  Serial.print(" rollval: ");
  Serial.print(dataroll);
  Serial.print(" left: ");
  Serial.print(data.left);
  Serial.print(" right: ");
  Serial.println(data.right); 
}
