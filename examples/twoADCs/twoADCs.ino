//  This library is made to interface with various  Linear Technology (LTC)
//  ADCs with have an SPI interface. This library uses the hardware SPI library,
//  so the correct pin assignments can be found at http://arduino.cc/en/Reference/SPI.
//  The chip select pin (CS) is choosen in the constructor.
//
//  This library is written by and copyright to Martin Hans under the Creative Commons Attribution-ShareAlike 3.0 Unported license.
//
//  It is based loosely on the ADC library by Jan Dalheimer, see https://sites.google.com/site/alternativarduino/english/librarys/adc
//
//  I release this library without any warrant and with VERY limited support.
//


#include "SPI.h"
#include "ltcadc.h"

LTCADC adc_hi(LTC2439_1, 10);  //create an instace of the library with the MAX1272 as ADC and digital pin 10 as chip select
LTCADC adc_lo(LTC2439_1, 9);   //create an instace of the library with the MAX1272 as ADC and digital pin 10 as chip select

void setup(){
  Serial.begin(9600);  //Start the serial port at 9600 baud
}

void loop(){    
    for(int channel = 0; channel < 32 ; channel++) {
        Serial.println("starting.");
        int value;
        if(channel < 16) {
            value = adc_lo.readADC(channel);
        } else {
            value = adc_hi.readADC(channel);
        }        
        
        Serial.print("channel ");
        Serial.print(channel);
        Serial.print(" : ");
        Serial.println(value);

        Serial.println();

        delay(1000);
    }  
}

  
