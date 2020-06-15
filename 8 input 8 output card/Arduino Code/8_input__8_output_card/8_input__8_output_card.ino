#include <Auto485.h>
#include <CMRI.h>
//Author: Michael Adams (<http://www.michael.net.nz>)
// Copyright (C) 2012 Michael D K Adams.
// Released under the MIT license.

// eight inputs
#define input_1 A5
#define input_2 4
#define input_3 3
#define input_4 A4
#define input_5 A3
#define input_6 A2
#define input_7 A1
#define input_8 A0

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

#define CMRI_ADDR 0
CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {
     bus.begin(9600,SERIAL_8N2);
     
     pinMode(input_1, INPUT_PULLUP);
     pinMode(input_2, INPUT_PULLUP);
     pinMode(input_3, INPUT_PULLUP);
     pinMode(input_4, INPUT_PULLUP);
     pinMode(input_5, INPUT_PULLUP);
     pinMode(input_6, INPUT_PULLUP);
     pinMode(input_7, INPUT_PULLUP);
     pinMode(input_8, INPUT_PULLUP);

     pinMode(output_1, OUTPUT);
     pinMode(output_2, OUTPUT);
     pinMode(output_3, OUTPUT);
     pinMode(output_4, OUTPUT);
     pinMode(output_5, OUTPUT);
     pinMode(output_6, OUTPUT);
     pinMode(output_7, OUTPUT);
     pinMode(output_8, OUTPUT);

     Serial.begin(9600, SERIAL_8N2);
     //Serial.println("cm 10 open");

}

void loop() {
     
     // Inputs to C/MRI
     cmri.process();

     boolean a = LOW;
     boolean b = LOW;
     int offset = 0;
     
     for (int i = 1; i <= 8; i++) {
      
        switch (i) {
            case 1:
                 a = digitalRead(input_1);
                 break;
            case 2:
                a = digitalRead(input_2);
                break;
            case 3:
                a = digitalRead(input_3);
                break;
            case 4:
                a = digitalRead(input_4);
                break;
            case 5:
                a = digitalRead(input_5);
                break;
            case 6:
                a = digitalRead(input_6);
                break;
            case 7:
                a = digitalRead(input_7);
                break;
            case 8:
                a = digitalRead(input_8);
                break;    
            default:
                // statements
                break;
        }
        if (a == LOW) {
           b = HIGH;
        }
        else {
          b = LOW;
        }
        offset = i-1;
        cmri.set_bit(offset,b);
     }

boolean x = LOW;
boolean y = LOW;

     for (int i = 0; i <= 7; i++) {
      x = cmri.get_bit(i);
        if (x == LOW) {
           y = HIGH;
        }
        else {
          y = LOW;
        }
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


}
