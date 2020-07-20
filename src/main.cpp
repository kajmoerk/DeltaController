#include <Arduino.h>
#include <stdlib.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Adafruit_PWMServoDriver.h>
#include <SocketIoClient.h>
//#include <WebSocketsServer.h>
#include "iostream"
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;
//WebSocketsServer webSocket = WebSocketsServer(81);
//Servo setup:
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
  uint8_t servonum = 0;
 #define SERVOMIN0   110// This is the 'minimum' pulse length count (out of 4096)
  #define SERVOMAX0   460// This is the 'maximum' pulse length count (out of 4096)
  #define SERVOMIN1   110// This is the 'minimum' pulse length count (out of 4096)
  #define SERVOMAX1  460 // This is the 'maximum' pulse length count (out of 4096)
  #define SERVOMIN2   110// This is the 'minimum' pulse length count (out of 4096)
  #define SERVOMAX2  460 // This is the 'maximum' pulse length count (out of 4096)
  #define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void joint1event(const char * payload, size_t length) {
  //float pulselength = map(atof(payload), 0, 180, SERVOMIN0, SERVOMAX0);
  pwm.setPWM(0, 0, atof(payload));
  //USE_SERIAL.print(pulselength);
}
void joint2event(const char * payload, size_t length) {
  //float pulselength = map(atof(payload), 0, 180, SERVOMIN1, SERVOMAX1);
  pwm.setPWM(1, 0, atof(payload));
  //USE_SERIAL.print(pulselength);
}
void joint3event(const char * payload, size_t length) {
  //USE_SERIAL.printf("got message: %s\n", payload);
  //float pulselength = map(atof(payload), 0, 180, SERVOMIN2, SERVOMAX2);
  pwm.setPWM(2, 0, atof(payload));
  USE_SERIAL.print(atof(payload));
}

void setup() {
    USE_SERIAL.begin(9600);

    //USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    pwm.begin();
    pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
    pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }

    WiFiMulti.addAP("Waoo4920_3N4H", "sisse246");

    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    webSocket.begin("192.168.1.156", 5000);
    webSocket.on("joint1", joint1event);
    webSocket.on("joint2", joint2event);
    webSocket.on("joint3", joint3event);
}
void loop() {
    webSocket.loop();
}