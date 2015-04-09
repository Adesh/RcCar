Attempt to make simple remote controll car using Arduino and Bluetooth module.
Aiming to control car using Desktop and Android application

RcCar.ino file contains Arduino code
AfMotor.h is library dependancy for DC motor shield to work, Copy the Afmotor directory to your arduino library directory in local machine

Car Hardware detail:
Arduino mega
Motor Sheild (with two IC-L293D)
DC motors (4 DC motors)
Bluetooth module (JY-MCU HC-05)

Car remote (Desktop App) detail:
Chrome app has been developed to controll RC car using Bluetooth serial port.

Car remote (Android App) detail:  
to be developed in future


Command to control car:
0 - stop
1 - forward
2 - backward
3 - left
4 - right
