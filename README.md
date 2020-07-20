# DeltaController
A Deltacontroller that runs on the esp8266 mircoprocessor.
The controller acts like a client and waits on Socket.IO emits from the DeltaRobotServer: https://github.com/kajmoerk/DeltaRobotServer.git
and sends it via i2c to a Adafruits 16-Channel 12-bit PWM/Servo Driver.
