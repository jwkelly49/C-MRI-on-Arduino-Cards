#include <Auto485.h>
// Arduino Standard Library

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
#define input_9 12
#define input_10 11
#define input_11 10
#define input_12 9
#define input_13 8
#define input_14 7
#define input_15 6
#define input_16 5

#define DE_PIN 2
Auto485 bus(DE_PIN); 


#define CMRI_ADDR 4
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
     pinMode(input_9, INPUT_PULLUP);
     pinMode(input_10, INPUT_PULLUP);
     pinMode(input_11, INPUT_PULLUP);
     pinMode(input_12, INPUT_PULLUP);
     pinMode(input_13, INPUT_PULLUP);
     pinMode(input_14, INPUT_PULLUP);
     pinMode(input_15, INPUT_PULLUP);
     pinMode(input_16, INPUT_PULLUP);

}

void loop() {
     
     // Inputs to C/MRI
     cmri.process();

     boolean a = LOW;
     boolean b = LOW;
     
     for (int i = 0; i <= 15; i++) {
      
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
             case 8:
                 a = digitalRead(input_9);
                 break;
            case 9:
                a = digitalRead(input_10);
                break;
            case 10:
                a = digitalRead(input_11);
                break;
            case 11:
                a = digitalRead(input_12);
                break;
            case 12:
                a = digitalRead(input_13);
                break;
            case 13:
                a = digitalRead(input_14);
                break;
            case 14:
                a = digitalRead(input_15);
                break;
            case 15:
                a = digitalRead(input_16);
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
        cmri.set_bit(i,b);
     }


}
