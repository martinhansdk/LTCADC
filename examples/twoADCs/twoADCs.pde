//  This library is made to interface with various ADCs with have an SPI interface. This library
//  does not use the hardware SPI interface so it's possible to use any pin, just change the defines for the pins
//  As default, this librarys uses p digital pin 11 as MOSI, 12 as MISO and 13 as Clock pin.
//  The chip select pin (CS) is choosen in the constructor.
//
//  This library is written by and copyright to Jan Dalheimer under the Creative Commons Attribution-ShareAlike 3.0 Unported license.
//
//  I release this library without any warrant and with VERY limited support.
//
//  This example uses the MAX1272 with digital pin 10 as chip select (CS). It prints the value via serial to the computer
//

#include <ltcadc.h>

LTCADC adc_a(LTC2439_1, 10);  //create an instace of the library with the MAX1272 as ADC and digital pin 10 as chip select
LTCADC adc_b(LTC2439_1, 9);   //create an instace of the library with the MAX1272 as ADC and digital pin 10 as chip select

void setup(){
  Serial.begin(9600);  //Start the serial port at 9600 baud
}

void loop(){    
    for(int channel = 0; channel < 32 ; channel++) {
        int value;
        if(channel < 16) {
            value = adc_lo.readADC(channel);
        } else {
            value = adc_hi.readADC(channel);
        }
        
        Serial.print("channel ");
        Serial.print(channel);
        Serial.print(" : ")
        Serial.println(value);

        Serial.println();    

        delay(1000);
    }  
}


