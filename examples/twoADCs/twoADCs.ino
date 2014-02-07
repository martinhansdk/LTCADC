//  This library is made to interface with various  Linear Technology (LTC)
//  ADCs with have an SPI interface. This library uses the hardware SPI library,
//  so the correct pin assignments can be found at http://arduino.cc/en/Reference/SPI.
//  The chip select pin (CS) is choosen in the constructor.
//
//  This library is written by and copyright to Martin Hans under the Creative Commons Attribution license.
//  Get the latest version at http://github.com/martinhansdk/LTCADC
//
//  It is based loosely on the ADC library by Jan Dalheimer, see https://sites.google.com/site/alternativarduino/english/librarys/adc
//
//  I release this library without any warranty and with VERY limited support.
//

        
#include "SPI.h"
#include "ltcadc.h"

LTCADC adc_hi(LTC2439_1, 10);  //create an instace of the library with the LTC2439-1 as ADC and digital pin 10 as chip select
LTCADC adc_lo(LTC2439_1, 9);   //create an instace of the library with the LTC2439-1 as ADC and digital pin 9 as chip select

const double Vref_mV = 1250.0;
const double valueMax = 65535;

void setup(){
  Serial.begin(9600);  //Start the serial port at 9600 baud
  SPI.begin();
  
} 

void loop(){    
    for(int channel = 0; channel < 32 ; channel++) { 
        long value;
        
        if(channel < 16) {
            value = adc_lo.readADC(LTC_CHANNEL_COMMON | channel);
        } else {
            value = adc_hi.readADC(LTC_CHANNEL_COMMON | (channel - 16));
        }        
        
        double voltage_mV = value * Vref_mV / valueMax;        
        
        Serial.print("channel ");
        Serial.print(channel);
        
        Serial.print(" : ");
        Serial.print(value);
        
        Serial.print(" = ");
        Serial.print(voltage_mV);
        Serial.print("mV");        
        
        if(value == 32768)
          Serial.print(" OVERFLOW");
          
        Serial.println();
        
    }  
    Serial.println();
}

  
