
#include "ltc_utility.h"

long interpretADCResult(long rawValue, uint8_t databits, long dataMask) {
    bool complete = !(rawValue & (1L << (databits + 1)));
    bool positive = rawValue & (1L << databits);

    if(!complete) {
        return 99999999;
    }

    long result = rawValue & dataMask;

    if(!positive && result != 0) {
        result = result | (~dataMask); // sign extend
    }

    return result;
}