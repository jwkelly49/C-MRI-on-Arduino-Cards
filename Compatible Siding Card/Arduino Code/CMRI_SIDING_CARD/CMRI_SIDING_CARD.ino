#include <Auto485.h>
#include <CMRI.h>

// three inputs
#define Mainline A4
#define Diverging 4
#define OSdetection 3

// signal head CH1  -- A N. Passing siding facing top head
#define Agreen A3                      
#define Ayellow A2                     
#define Ared A1

// signal head CH2 -- A N. Passing siding facing bottom head
#define AbottomGreen A0                
#define AbottomRed 13

// signal head CH3 -- B N passing siding trailing top head
#define Bgreen 12
#define Byellow 11
#define Bred 10

// signal head CH4 -- B N passing siding trailing bottom head
#define BbottomRed 9

// signal head CH5 -- C N. passing siding dwarf signal
#define Cgreen 8
#define Cred 7

// outputs to Tortoise pins 1 and 8
#define Tmainline 6
#define Tdiverging 5

#define DE_PIN 2
Auto485 bus(DE_PIN); 

#define CMRI_ADDR 0
CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {
     bus.begin(9600,SERIAL_8N2);
     
     pinMode(Mainline, INPUT_PULLUP);
     pinMode(Diverging, INPUT_PULLUP);
     pinMode(OSdetection, INPUT_PULLUP);
     
     pinMode(Agreen, OUTPUT);
     pinMode(Ayellow, OUTPUT);
     pinMode(Ared, OUTPUT);
     
     pinMode(AbottomGreen, OUTPUT);
     pinMode(AbottomRed, OUTPUT);
     
     pinMode(Bgreen, OUTPUT);
     pinMode(Byellow, OUTPUT);
     pinMode(Bred, OUTPUT);
     
     pinMode(BbottomRed, OUTPUT);
     
     pinMode(Cgreen, OUTPUT);
     pinMode(Cred, OUTPUT);
     
     pinMode(Tmainline, OUTPUT);
     pinMode(Tdiverging, OUTPUT);

     //Serial.begin(9600);
     //Serial.println("cm 10 open");
}

void loop() {
     
     // Inputs to C/MRI
     cmri.process();
     cmri.set_bit(0, digitalRead(Mainline));
     cmri.set_bit(1,digitalRead(Diverging));
     cmri.set_bit(2,digitalRead(OSdetection));
     
     // Output from C/MRI 
     digitalWrite(Agreen, cmri.get_bit(0));  
     digitalWrite(Ayellow, cmri.get_bit(1));
     digitalWrite(Ared, cmri.get_bit(2));
    
      
     digitalWrite(AbottomGreen, cmri.get_bit(3)); 
     digitalWrite(AbottomRed, cmri.get_bit(4));
     
     digitalWrite(Bgreen, cmri.get_bit(5));
     digitalWrite(Byellow, cmri.get_bit(6)); 
     digitalWrite(Bred, cmri.get_bit(7));
     
     digitalWrite(BbottomRed, cmri.get_bit(8));
     
     digitalWrite(Cgreen, cmri.get_bit(9)); 
     digitalWrite(Cred, cmri.get_bit(10));
     
     digitalWrite(Tmainline, cmri.get_bit(11));
     digitalWrite(Tdiverging, cmri.get_bit(12));
     
     
         
}
