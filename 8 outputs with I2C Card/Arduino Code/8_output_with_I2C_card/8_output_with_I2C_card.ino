#include <Auto485.h>
#include <CMRI.h>
// Author: Michael Adams (<http://www.michael.net.nz>)
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

// eight outputs
#define output_1 12                     
#define output_2 11                   
#define output_3 10
#define output_4 9             
#define output_5 8
#define output_6 7
#define output_7 6
#define output_8 5

#define DE_PIN 2
Auto485 bus(DE_PIN); 

#define CMRI_ADDR 4
CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {
     pwm.begin();
     bus.begin(9600,SERIAL_8N2);
     pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
     yield();

     // start the bus communication
     bus.begin(9600,SERIAL_8N2);
     
     pinMode(output_1, OUTPUT);
     pinMode(output_2, OUTPUT);
     pinMode(output_3, OUTPUT);
     pinMode(output_4, OUTPUT);
     pinMode(output_5, OUTPUT);
     pinMode(output_6, OUTPUT);
     pinMode(output_7, OUTPUT);
     pinMode(output_8, OUTPUT);
     pinMode(LED_BUILTIN, OUTPUT);
     
}

void loop() {
     
     // Inputs to C/MRI
     cmri.process();

boolean x = LOW;
boolean y = LOW;
// read first 8 bits (lights) from C/MRI and set
// Arduino hardware bits

     for (int i = 0; i <= 7; i++) {
      y = cmri.get_bit(i);
        switch (i) {
            case 0:
                 digitalWrite(output_1,y);
                 break;
            case 1:
                digitalWrite(output_2,y);
                break;
            case 2:
                digitalWrite(output_3,y);
                break;
            case 3:
                digitalWrite(output_4,y);
                break;
            case 4:
                digitalWrite(output_5,y);
                break;
            case 5:
                digitalWrite(output_6,y);
                break;
            case 6:
                digitalWrite(output_7,y);
                break;
            case 7:
                digitalWrite(output_8,y);
                break;    
            default:
                // statements
                break;
        }
     }


    // FOR cycles throuh 16 output bits (9-24) in the cmri object
    // sent to it from JMRI
    // and stores the value in test 
    int servo = 0;
    for (int i = 8; i <= 23; i++) {
        servo = i;
        servo = servo-8;     
        test = cmri.get_bit(i);
        // IF sets servo number
        if (test==HIGH) {
            pwm.setPWM(servo, 0, SERVOMAX);  // Closed
        } else {
            pwm.setPWM(servo, 0, SERVOMIN);  // Thrown
        }
}
}
