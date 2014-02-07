//  This library is made to interface with various Linear Technology (LTC)
//  ADCs with have an SPI interface. This library uses the hardware SPI library,
//  so the correct pin assignments can be found at http://arduino.cc/en/Reference/SPI.
//  The chip select pin (CS) is choosen in the constructor.
//
//  This library is written by and copyright to Martin Hans under the Creative Commons Attribution.
//
//  It is based loosely on the ADC library by Jan Dalheimer, see https://sites.google.com/site/alternativarduino/english/librarys/adc
//
//  I release this library without any warranty and with VERY limited support.
//

#ifndef LTCADC_H
#define LTCADC_H

#include <stdint.h>

#define LTC_CHANNEL_COMMON 0b00010000
#define LTC_CHANNEL_DIFFERENTIAL 0b00000000

typedef struct {
    uint8_t numberOfDataBits;
    uint8_t commandHeaderWithChannelSelect;
    uint8_t commandHeaderWithoutChannelSelect;
    uint8_t SPIBitOrder; // See http://arduino.cc/en/Reference/SPISetBitOrder
    uint8_t SPIDataMode; // See http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Clock_polarity_and_phase
    uint8_t SPIClockDivider;  // See http://arduino.cc/en/Reference/SPISetClockDivider
} ADCModel;

extern ADCModel LTC2439_1; 

class LTCADC
{
public:
    //constructors
    LTCADC(ADCModel model, int CSPin);

    //destructor
    ~LTCADC();

    // read 
    long readADC(int channel);

    // lower level methods

    // set the next channel to convert and start the conversion
    uint8_t startConversion(int channel);

    // check if the ADC has finished the conversion
    bool conversionEnded();

    // query the result of the conversion from the ADC and return the result. Note that this will trigger another conversion
    long readConversionResult();


    void selectSlave();
    void deselectSlave();

private:
    ADCModel model;

    //the Slave Select (SS) pin to be used by the arduino
    int SELPIN;
    unsigned long dataMask;
    unsigned long signExtendMask;
};

#endif // LTCADC_H