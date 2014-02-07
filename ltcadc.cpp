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

// NOCOMMIT: remove
#define EXTRA1 7
#define EXTRA2 6


#include "SPI.h"
#include "ltcadc.h"
#include "ltc_utility.h"

#include <Arduino.h>

ADCModel LTC2439_1 = {16, 0b10100000, 0b00000000, MSBFIRST, SPI_MODE0, SPI_CLOCK_DIV16};

LTCADC::LTCADC(ADCModel model, int CSPin) : model(model), SELPIN(CSPin)
{
    // construct data mask
    dataMask = 0L;
    for(int i=0 ; i < model.numberOfDataBits ; i++) {
        dataMask |= (1L << i);       
    }

    // initialize SPI interface
    SPI.begin();
    SPI.setBitOrder(model.SPIBitOrder);
    SPI.setDataMode(model.SPIDataMode);
    SPI.setClockDivider(model.SPIClockDivider);
    pinMode(SELPIN, OUTPUT);   

    // NOCOMMIT: remove
    pinMode(EXTRA1, OUTPUT); 
    pinMode(EXTRA2, OUTPUT); 
    digitalWrite(EXTRA1,LOW);
    digitalWrite(EXTRA2,LOW);

    //disable device to start with
    digitalWrite(SELPIN,HIGH);
}

LTCADC::~LTCADC()
{
}


long LTCADC::readADC(int channel)
{
    // set channel and initiate conversion
    startConversion(channel);

    return readConversionResult();
}

uint8_t LTCADC::startConversion(int channel) {
    uint8_t controlByte = model.commandHeaderWithChannelSelect | channel;

    // first send the channel number and initiate the conversion
    digitalWrite(EXTRA1, HIGH);
    digitalWrite(EXTRA1, LOW);

    selectSlave();
    // we cannot initiate a new conversion unless the previous one is finished
    while(!conversionEnded()) {}
    SPI.transfer(controlByte);
    deselectSlave();

    return 0;
}

bool LTCADC::conversionEnded() {
    return (digitalRead(12) == 0);
}

long LTCADC::readConversionResult() {
    // initiate conversion
    selectSlave();

    // keep polling until the ADC reports that the data is complete
    while(!conversionEnded()) {}


    // NOCOMMIT: 
    digitalWrite(EXTRA2, HIGH);
    digitalWrite(EXTRA2, LOW);

    int8_t bitsleft = model.numberOfDataBits + 3; // 3 status bits before data

    long result = 0;

    while(bitsleft > 0) {
        result <<= 8;
        result |= SPI.transfer(model.commandHeaderWithoutChannelSelect);
        bitsleft -= 8;
    }    
    deselectSlave();

    result >>= -bitsleft;
    
    return interpretADCResult(result, model.numberOfDataBits, dataMask);
}

void LTCADC::selectSlave() {
    digitalWrite(SELPIN, LOW);
}

void LTCADC::deselectSlave() {
    digitalWrite(SELPIN, HIGH);
}