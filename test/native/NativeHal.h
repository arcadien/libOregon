#pragma once
#include <oregon.h> /* Hal */

class NativeHal : public Hal
{
public:
    NativeHal() : Hal()
    {
        reset();
    }

    void reset()
    {
        radioOutputIndex = 0;
        memset(&radioOutput[0], 0, (128 / sizeof(int)));
    }

    void rfHigh()
    {
        radioOutput[radioOutputIndex] = 'H';
        radioOutputIndex++;
    }
    void rfLow()
    {
        radioOutput[radioOutputIndex] = 'L';
        radioOutputIndex++;
    }

    void shortWait()
    {
        radioOutput[radioOutputIndex] = 'S';
        radioOutputIndex++;
    }

    void longWait()
    {
        radioOutput[radioOutputIndex] = 'W';
        radioOutputIndex++;
    }

    char radioOutput[128];

private:
    uint8_t radioOutputIndex;
};