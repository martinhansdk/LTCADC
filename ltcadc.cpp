//  This library is made to interface with various  Linear Technology (LTC)
//  ADCs with have an SPI interface. This library uses the hardware SPI library,
//  so the correct pin assignments can be found at http://arduino.cc/en/Reference/SPI.
//  The chip select pin (CS) is choosen in the constructor.
//
//  This library is written by and copyright to Martin Hans under the Creative Commons Attribution-ShareAlike 3.0 Unported license.
//  Get the latest version at http://github.com/martinhansdk/LTCADC
//
//  It is based loosely on the ADC library by Jan Dalheimer, see https://sites.google.com/site/alternativarduino/english/librarys/adc
//
//  I release this library without any warrant and with VERY limited support.
//



#include "SPI.h"
#include "ltcadc.h"

#include <Arduino.h>

extern ADCModel LTC2439_1 = {16, 0b10100000, 0b10000000, MSBFIRST, SPI_MODE0, SPI_CLOCK_DIV4};

LTCADC::LTCADC(ADCModel model, int CSPin) : model(model), SELPIN(CSPin)
{
    // construct data mask
    dataMask = 0;
    for(int i=0 ; i < model.numberOfDataBits ; i++) {
        dataMask |= (1 << i);
    }

    // initialize SPI interface
    SPI.begin();
    SPI.setBitOrder(model.SPIBitOrder);
    SPI.setDataMode(model.SPIDataMode);
    SPI.setClockDivider(model.SPIClockDivider);
    pinMode(SELPIN, OUTPUT);   

    //disable device to start with
    digitalWrite(SELPIN,HIGH);
}

LTCADC::~LTCADC()
{
}


unsigned int LTCADC::readADC(int channel)
{
    // set channel and initiate conversion
    startConversion(channel);

    // keep polling until the ADC reports that the data is complete
    while(!conversionEnded()) {}

    // read out the result
    return readConversionResult();
}

void LTCADC::startConversion(int channel) {
    uint8_t controlByte = model.commandHeaderWithChannelSelect & channel;

    // first send the channel number and initiate the conversion
    digitalWrite(SELPIN, LOW);
    uint8_t result1 = SPI.transfer(controlByte);
    digitalWrite(SELPIN, HIGH);
}

bool LTCADC::conversionEnded() {
    bool ended;
    digitalWrite(SELPIN, LOW);
    ended = (digitalRead(MOSI) == 0);
    digitalWrite(SELPIN, HIGH);

    return ended;
}

unsigned int LTCADC::readConversionResult() {
    int8_t bitsleft = model.numberOfDataBits;
    unsigned result = 0;
    while(bitsleft > 0) {
        result <<= 8;
        result &= SPI.transfer(model.commandHeaderWithoutChannelSelect);
        bitsleft -= 8;
    }

    return result & dataMask;
}
