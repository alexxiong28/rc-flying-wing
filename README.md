# rc-flying-wing
making an arduino based rc flying wing
nrf24 radio moudle is used to communcate between the transmitter and receiver
2500kv bldc motor is used with 3s 1300mAh lipo
current issues: unprecise input value due to poor connection/poor joystick quality, nrf24 shutting down due to insufficient power from arduino nano.

source of inspiration https://www.rcpano.net/2020/04/09/how-to-make-6-channel-radio-control-for-models-diy-proportional-rc/


ver2 transmitter: attempt to fix joystick issue, use a computer keyboard and python to send serial data to arduino nano and then transmitt them to the receiver using the nrf24
