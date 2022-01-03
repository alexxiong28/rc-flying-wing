//  6 Channel Receiver | 6 Kanal Alıcı
//  PWM output on pins D2, D3, D4, D5, D6, D7 (Çıkış pinleri)

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int ch_width_1 = 0;
int ch_width_2 = 1800;
int ch_width_3 = 1350;
int ch_width_4 = 0;
int ch_width_5 = 0;
int ch_width_6 = 0;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;
Servo ch5;
Servo ch6;

struct Signal {
byte throttle;
byte left;
byte right;      
byte pitch;
byte roll;
byte yaw;
byte aux1;
byte aux2;
};

Signal data;

const uint64_t pipeIn = 0xE9E8F0F0E1LL;
RF24 radio(9, 10); 

void ResetData()
{
// Define the inicial value of each data input. | Veri girişlerinin başlangıç değerleri
// The middle position for Potenciometers. (254/2=127) | Potansiyometreler için orta konum
data.left = 127;   // Center | Merkez
data.right = 127;  // Center | Merkez
data.throttle = 12; // Motor Stop | Motor Kapalı
data.yaw = 127;   // Center | Merkez
data.aux1 = 127;   // Center | Merkez
data.aux2 = 127;   // Center | Merkez
//radio.begin();
//radio.startListening();
}

void setup()
{
  Serial.begin(9600);
  //Set the pins for each PWM signal | Her bir PWM sinyal için pinler belirleniyor.
  ch1.attach(4);
  ch2.attach(3);
  ch3.attach(9);
  pinMode(LED_BUILTIN, OUTPUT);

  //Configure the NRF24 module
  ResetData();
  radio.begin();
  radio.openReadingPipe(1,pipeIn);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening(); //start the radio comunication for receiver | Alıcı olarak sinyal iletişimi başlatılıyor

  pinMode(6,OUTPUT);

}

unsigned long lastRecvTime = 0;

void recvData()
{
while ( radio.available() ) {
radio.read(&data, sizeof(Signal));
lastRecvTime = millis();   // receive the data | data alınıyor
}
}

int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, 0, 255);
  if ( val < middle )
  val = map(val, 0, 128, lower,middle);
  else
  val = map(val, 128, 255, middle, upper);
  return ( reverse ? 255 - val : val );
}

void loop()
{
  if(radio.available()){
    radio.read(&data, sizeof(Signal));
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, HIGH);
  }



ch_width_2 = map(data.right, 0,255 , 2000,1200);     // pin D3 (PWM signal)
ch_width_1 = map(data.throttle, 0, 255, 800, 2000);     // pin D4 (PWM signal)
ch_width_3 = map(data.left, 0, 255, 1000, 1800);     // pin D2 (PWM signal)

  Serial.print(" left: ");
  Serial.print(ch_width_2);
  Serial.print(" right: ");
  Serial.println(ch_width_3); 

// Write the PWM signal | PWM sinyaller çıkışlara gönderiliyor
ch1.writeMicroseconds(ch_width_1);
ch2.writeMicroseconds(ch_width_2);
ch3.writeMicroseconds(ch_width_3);

}
