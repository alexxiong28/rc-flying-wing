# rc-flying-wing
making an arduino based rc flying wing
nrf24 radio moudle is used to communcate between the transmitter and receiver
2500kv bldc motor is used with 3s 1300mAh lipo
current issues: unprecise input value due to poor connection/poor joystick quality, nrf24 shutting down due to insufficient power from arduino nano.

source of inspiration https://www.rcpano.net/2020/04/09/how-to-make-6-channel-radio-control-for-models-diy-proportional-rc/


ver2 transmitter: attempt to fix joystick issue, use a computer keyboard and python to send serial data to arduino nano and then transmitt them to the receiver using the nrf24

ver1 flying wing with nrf24, arduino nano and mpu6050
![271921723_1417079458707755_8588626153284196107_n](https://user-images.githubusercontent.com/34170966/150932029-b5f3b6a2-bc73-4bd4-8bc3-4430e5384eb1.jpg)

Lora module connectivity test using stm32 bluepill as mcu


https://user-images.githubusercontent.com/34170966/150932194-9416ed40-8e7e-4712-861d-43243b0b7922.mp4

