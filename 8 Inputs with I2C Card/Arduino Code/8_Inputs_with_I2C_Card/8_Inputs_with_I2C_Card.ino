#include <Auto485.h>
// Arduino Standard Library

#include <CMRI.h>
//Author: Michael Adams (<http://www.michael.net.nz>)
// Copyright (C) 2012 Michael D K Adams.
// Released under the MIT license.

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
// create an object named pwm
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

// test holds the value from CMRI output bits
boolean test = LOW;

// assign eight input names to Arduino pin numbers
#define input_1 12
#define input_2 11
#define input_3 10
#define input_4 9
#define input_5 8
#define input_6 7
#define input_7 6
#define input_8 5

//create a bus object using pin 2 for control
#define DE_PIN 2
Auto485 bus(DE_PIN); 

// create a cmri object, give it an address + type of CMRI card + communicate on bus
#define CMRI_ADDR 4
CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {

     // start pwm and assign a frequence
     pwm.begin();
     pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
     yield();

     // start the bus communication
     bus.begin(9600,SERIAL_8N2);
     
     // tell Arduino how pins will be used
     pinMode(input_1, INPUT_PULLUP);
     pinMode(input_2, INPUT_PULLUP);
     pinMode(input_3, INPUT_PULLUP);
     pinMode(input_4, INPUT_PULLUP);
     pinMode(input_5, INPUT_PULLUP);
     pinMode(input_6, INPUT_PULLUP);
     pinMode(input_7, INPUT_PULLUP);
     pinMode(input_8, INPUT_PULLUP);

}

void loop() {
     
     // wake up cmri object
     cmri.process();

     boolean a = LOW;
     boolean b = LOW;

     // FOR cycles through 8 Arduino inputs
     // and saves the value in a 
     for (int i = 0; i <= 7; i++) {
        switch (i) {
            case 0:
                 a = digitalRead(input_1);
                 break;
            case 1:
                a = digitalRead(input_2);
                break;
            case 2:
                a = digitalRead(input_3);
                break;
            case 3:
                a = digitalRead(input_4);
                break;
            case 4:
                a = digitalRead(input_5);
                break;
            case 5:
                a = digitalRead(input_6);
                break;
            case 6:
                a = digitalRead(input_7);
                break;
            case 7:
                a = digitalRead(input_8);
                break;    
            default:
                // statements
                break;
        }
        // IF - ELSE inverts the Arduino bits
        // and stores the new value in b
        if (a == LOW) {
           b = HIGH;
        }
        else {
          b = LOW;
        }
        // i = cmri bitnumber b = value to send
        // set_bit passes value to cmri object so it
        // can be passed out to JMRI
        cmri.set_bit(i,b);
     }

    // FOR cycles throuh 16 output bits in the cmri object
    // sent to it from JMRI
    // and stores the value in test 
    for (int i = 0; i <= 15; i++) {     
        test = cmri.get_bit(i);
        // IF sets servo number (i)
        if (test==HIGH) {
            pwm.setPWM(i, 0, SERVOMAX );  // Closed
        } else {
            pwm.setPWM(i, 0, SERVOMIN );  // Thrown
        }
}
}
