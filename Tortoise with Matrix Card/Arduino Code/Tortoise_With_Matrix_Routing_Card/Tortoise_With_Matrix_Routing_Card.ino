#include <Auto485.h>
#include <CMRI.h>

// Asign names to Arduino pins
#define TortoiseA_1 9
#define TortoiseA_2 10
#define TortoiseB_1 11
#define TortoiseB_2 12
#define TortoiseC_1 8
#define TortoiseC_2 7
#define TortoiseD_1 6
#define TortoiseD_2 5
int startup = 1; 

// Asign name to Arduino 485 chip control pin
// and create a bus object
#define DE_PIN 2
Auto485 bus(DE_PIN); 

// ********* change this number (default is 0) to assign 
// ********* new address for this CMRI module.
#define CMRI_ADDR 0

// Create a CMRI module object
CMRI cmri(CMRI_ADDR, 24, 48, bus);


void setup() {
     // start 485 communication
     bus.begin(9600,SERIAL_8N2);
     Serial.begin(9600, SERIAL_8N2);
     // set Arduino pins to outputs
     pinMode(TortoiseA_1, OUTPUT);
     pinMode(TortoiseA_2, OUTPUT);
     pinMode(TortoiseB_1, OUTPUT);
     pinMode(TortoiseB_2, OUTPUT);
     pinMode(TortoiseC_1, OUTPUT);
     pinMode(TortoiseC_2, OUTPUT); 
     pinMode(TortoiseD_1, OUTPUT);
     pinMode(TortoiseD_2, OUTPUT);
}

void loop() {
     
      // pass stuff into and out of the CMRI object
      // the object gets and sends data via the bus (485 chip)
      cmri.process();
     
     // Outputs from C/MRI via JMRI
     // GET the cmri bit setting and WRITE it
     // to the Arduino pin (output)
     
     digitalWrite(TortoiseA_1, cmri.get_bit(0));  
     digitalWrite(TortoiseA_2, cmri.get_bit(1));
     digitalWrite(TortoiseB_1, cmri.get_bit(2));
     digitalWrite(TortoiseB_2, cmri.get_bit(3)); 
     digitalWrite(TortoiseC_1, cmri.get_bit(4));
     digitalWrite(TortoiseC_2, cmri.get_bit(5));
     digitalWrite(TortoiseD_1, cmri.get_bit(6)); 
     digitalWrite(TortoiseD_2, cmri.get_bit(7));
        
}
